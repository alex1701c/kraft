/***************************************************************************
                          docdigestview.h  -
                             -------------------
    begin                : Wed Mar 15 2006
    copyright            : (C) 2006 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef DOCDIGESTVIEW_H
#define DOCDIGESTVIEW_H

#include <qwidget.h>
#include <qmap.h>

#include "docdigest.h"

class KListView;
class FilterHeader;


class DocDigestView : public QWidget
{
  Q_OBJECT

public:
  DocDigestView( QWidget *parent );
  ~DocDigestView();

  void addLatestDocs( DocDigestList );

  QString currentDocumentId();
public slots:
  void slotNewDoc();
  void slotDocOpenRequest( QListViewItem * );

protected slots:
  void addChapter( const QString&, DocDigestList );
  void slotOpenCurrentDoc();
  void slotCurrentChanged( QListViewItem* );
signals:
  void createDocument();
  void openDocument( const QString& );
  void selectionChanged( const QString& );
  void printDocument( const QString& );
private:
  KListView *mListView;
  FilterHeader *mFilterHeader;

  QMap<QListViewItem*, QString> mDocIdDict;
};

#endif
