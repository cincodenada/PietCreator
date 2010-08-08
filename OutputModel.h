/*
    Copyright (C) 2010 Casey Link <unnamedrambler@gmail.com>
    Copyright 2007 Andreas Pakulat <apaku@gmx.de>

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

#ifndef OUTPUTMODEL_H
#define OUTPUTMODEL_H

#include <qstandarditemmodel.h>


class OutputModel : public QStandardItemModel
{
Q_OBJECT
public:
    OutputModel( QObject* parent = 0 );
public Q_SLOTS:
    void appendString( const QString & text );
    void appendLine( const QString& line );
    void appendLines( const QStringList& lines );
};

#endif // OUTPUTMODEL_H
