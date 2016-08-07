/*
    Copyright (C) 2010 Casey Link <unnamedrambler@gmail.com>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef RUNCONTROLLER_H
#define RUNCONTROLLER_H

#include <QObject>
#include <QTextStream>
#include <QImage>
#include <QMutex>
#include <QWaitCondition>
#include <QTimer>

#ifdef Q_WS_WIN
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#endif

class QSocketNotifier;
class NPietObserver;

struct trace_step;
struct trace_action;

class RunController : public QObject
{
    Q_OBJECT
public:
    RunController();
    ~RunController();

    void putInt( int i );
    void putChar( const QChar & c );

    void setMaxStep( int max_step );
    int getMaxStep();

    int getInt();
    char getChar();

signals:
    void newOutput( const QString & );
    void stepped( trace_step* );
    void actionChanged( trace_action* );
    void stopped();
    void debugStarted();
    void waitingForInt();
    void waitingForChar();

public slots:
    void slotThreadStarted();

    void debugSource( const QImage &source );
    bool runSource( const QImage &source );
    void pixelChanged( int x, int y, QRgb color );

    void step();
    void abort();
private slots:
    void stdoutReadyRead();
	void win32OutputTimeout();

    bool initialize( const QImage &source );
    void execute();

    void slotStepped( trace_step* );
    void slotAction( trace_action* );

    void tick();

private:
    void captureStdout();
    bool prepare();
    void finish();

    /** Call with mutex locked */
    void stop();

    //Capturing program output
    QTextStream* mStdOut;
#ifndef Q_WS_WIN
    QSocketNotifier* mNotifier;
    int mPipeFd[2]; /**< [0] is read end, [1] is write end */
    int mOrigFd;
    int mOrigFdCopy;
#else
	HANDLE mPipeRead;
	HANDLE mPipeWrite;
	HANDLE mOldStdoutHandle;
#endif

    // Reacting to notifications from npiet
    NPietObserver* mObserver;


    bool mPrepared;
    QImage mSource;

    QMutex mMutex;
    QWaitCondition mWaitCond;
    bool mAbort;
    bool mExecuting;
    bool mDebugging;
    QTimer* mTimer;
	QTimer* mOutputTimer;

    char mChar;
    int mInt;
};

#endif // RUNCONTROLLER_H
