/***************************************************************************
                      kraftview.h  - view of kraft documents
                             -------------------
    begin                : Mit Dez 31 19:24:05 CET 2003
    copyright            : (C) 2003 by Klaas Freitag
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

#ifndef KRAFTVIEW_H
#define KRAFTVIEW_H

/** The KraftView class provides the view widget for the KraftApp instance.
 * The View instance inherits QWidget as a base class and represents
 * the view object of a KTMainWindow. As KraftView is part of the
 * docuement-view model, it needs a reference to the document object
 * connected with it by the KraftApp class to manipulate and display
 * the document structure provided by the KraftDoc class.
 *
 * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
 * @version KDevelop version 0.4 code generation
 */

// include files for Qt
#include <QMap>
#include <QLabel>


#include <kdialog.h>
#include <kabc/addressee.h>

#include "kraftdoc.h"
#include "positionviewwidget.h"
#include "catalogtemplate.h"
#include "ui_docheader.h"
#include "ui_docfooter.h"

class PositionViewWidget;
class DocPosition;
class QLabel;
class QWidget;
class QResizeEvent;
class QSignalMapper;
class QStackedWidget;
class KVBox;
class QSplitter;
class DocPostCard;
class QTimer;
class CatalogSelection;
class KPushButton;
class DocAssistant;
class CalcPartList;
class AddressProvider;

class Katalog;
class KraftViewScroll;

using namespace KABC;

class KraftView : public KDialog
{
  Q_OBJECT
    public:
  /** Constructor for the main view */
  KraftView(QWidget *parent);
  /** Destructor for the main view */
  virtual ~KraftView();

  /** returns a pointer to the document connected to the view
      instance. Mind that this method requires a KraftApp instance as a
      parent * widget to get to the window document pointer by calling
      the KraftApp::getDocument() method.
      *
      * @see KraftApp#getDocument
      */
  KraftDoc *getDocument() const;

  /** contains the implementation for printing functionality */
  void print(QPrinter *pPrinter);

  void setup( DocGuardedPtr );


  typedef QMap<DocPositionBase*, PositionViewWidget*> PositionMap;

  DocPositionList currentPositionList();
  DocPositionBase::TaxType currentTaxSetting();

  public slots:
  void slotNewAddress( const Addressee& contact = Addressee(), bool interactive = true );
  void redrawDocument( );
  void slotModifiedPositions();
  void slotModifiedHeader();
  void slotModifiedFooter();

  void slotAddItem( Katalog*, CatalogTemplate* );
  void slotAddNewItem();
  void slotAddItems( Katalog*, CatalogTemplateList );

  void slotAddExtraPosition();
  void slotImportItems();
  void slotFocusItem( PositionViewWidget*,  int );
  void slotNewHeaderText( const QString& );
  void slotNewFooterText( const QString&  );
  void slotSwitchToPage( int );
  
  protected slots:
  void closeEvent(QCloseEvent *event);
  void redrawDocPositions( );
  void done( int );
  void slotMovePositionUp( int );
  void slotMovePositionDown( int );
  void slotDeletePosition( int );
  void slotUnlockPosition( int );
  void slotLockPosition( int );
  void slotPositionModified( int );
  void slotAboutToShow( QWidget* );
  void refreshPostCard( );
  void slotShowCatalog( bool );
  void slotShowTemplates( bool );

  void slotDocTypeChanged( const QString& );
  void slotLanguageSettings();
  void slotPickAddressee();
  void slotAddresseeFound( const QString&, const KABC::Addressee& );
  void slotTaxComboChanged( int );

signals:
  void selectPage( int );
  void viewClosed( bool, DocGuardedPtr );
  void positionSelected( Katalog*, void* );
private:
  void setupDocHeaderView();
  void setupItems();
  void setupFooter();
  void setupTextsView();
  void setMappingId( QWidget *, int );
  void setupMappers();
  void saveChanges();
  void discardChanges();
  bool documentModifiedMessageBox();

  PositionViewWidget *createPositionViewWidget( DocPositionBase*, int );

  QStringList generateLetterHead( Addressee adr );

  KraftViewScroll   *m_positionScroll;
  Ui::DocHeaderEdit *m_headerEdit;
  Ui::DocFooterEdit *m_footerEdit;

  PositionViewWidgetList mPositionWidgetList;

  QString mContactUid;
  DocGuardedPtr m_doc;
  QSignalMapper *mDeleteMapper;
  QSignalMapper *mMoveUpMapper;
  QSignalMapper *mMoveDownMapper;
  QSignalMapper *mUnlockPositionMapper;
  QSignalMapper *mLockPositionMapper;
  QSignalMapper *mModifiedMapper;

  AddressProvider *mAddressProvider;

  QLabel        *mDetailHeader;
  QSplitter     *mCSplit;
  KPushButton   *mCatalogToggle;
  QLabel        *mHelpLabel;

  QWidget        *mSumSpacer;
  QStackedWidget *mViewStack;
  KVBox          *mGlobalVBox;
  int             mHeaderId;
  DocAssistant   *mAssistant;
  double         mRememberAmount;
  QMap<dbID, CalcPartList> mCalculationsMap;

  bool           mModified;
  int            mTaxBefore;
  int            mDocPosEditorIndx;
};

#endif // KRAFTVIEW_H
