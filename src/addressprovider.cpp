/***************************************************************************
                          addressprovider.cpp  -
                             -------------------
    begin                : Fri Mar 4 2011
    copyright            : (C) 2011 by Klaas Freitag
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

#include "addressprovider.h"
#include <QDebug>

// FIXME this needs to change once there are more address book providers, ie.
// on Mac.
#include "addressprovider_akonadi.h"


/* ==================================================================================== */

AddressProvider::AddressProvider( QObject *parent )
  :QObject( parent ),
    _d( new AddressProviderPrivate(parent) )
{
    connect(_d, SIGNAL(addresseeFound( const QString&, const KContacts::Addressee& )),
            this, SIGNAL(addresseeFound( const QString&, const KContacts::Addressee& )));

    // emitted when the search is finished, even if there was no result.
    connect(_d, SIGNAL(finished(int)), this, SIGNAL(finished(int)));
}

void AddressProvider::lookupAddressee( const QString& uid )
{
    _d->lookupAddressee(uid);
}

KContacts::Addressee AddressProvider::getAddressee(const QModelIndex& indx)
{
    return _d->getAddressee(indx);
}

KContacts::Addressee AddressProvider::getAddressee( int row, const QModelIndex &parent)
{
    return _d->getAddressee(row, parent);
}

void AddressProvider::searchResult( KJob* job )
{
    _d->searchResult(job);
}

QAbstractItemModel *AddressProvider::model()
{
    return _d->model();
}

QString AddressProvider::formattedAddress( const KContacts::Addressee& contact ) const
{
  QString re;
  KContacts::Address address;

  address = contact.address( KContacts::Address::Pref );
  if( address.isEmpty() )
    address = contact.address(KContacts::Address::Work );
  if( address.isEmpty() )
    address = contact.address(KContacts::Address::Home );
  if( address.isEmpty() )
    address = contact.address(KContacts::Address::Postal );

  if( address.isEmpty() ) {
    re = contact.realName();
  } else {
    re = address.formattedAddress( contact.realName(), contact.organization() );
  }
  return re;
}

