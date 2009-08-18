/***************************************************************************
 *   Copyright (C) 2008-2009 by Heiko Koehn                                     *
 *   KoehnHeiko@googlemail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _TRIGGER_UNIT_H
#define _TRIGGER_UNIT_H

#include "TTrigger.h"
#include <list>
#include <map>
#include <QMutex>
#include <QDataStream>
#include <QTextBlock>

class TTrigger;
class Host;

class TriggerUnit
{
    friend class XMLexport;
    friend class XMLimport;
    
public:
                          TriggerUnit( Host * pHost ) : mpHost(pHost), mMaxID(0) {;}
    std::list<TTrigger *> getTriggerRootNodeList()   { QMutexLocker locker(& mTriggerUnitLock); return mTriggerRootNodeList; }
    TTrigger *            getTrigger( int id );
    void                  enableTrigger( QString & );
    void                  disableTrigger( QString & );
    void                  killTrigger( QString & name );
    bool                  registerTrigger( TTrigger * pT );
    void                  unregisterTrigger( TTrigger * pT );
    bool                  serialize( QDataStream & );
    bool                  restore( QDataStream &, bool );
    void                  reParentTrigger( int childID, int oldParentID, int newParentID );
    void                  processDataStream( QString &, int );
    void                  dump();
    void                  setTriggerStayOpen( QString, int );
    void                  stopAllTriggers();
    void                  reenableAllTriggers();
    std::list<TTrigger *> mCleanupList;
    qint64                getNewID();
    QMap<QString, TTrigger *> mLookupTable;
    QMutex                mTriggerUnitLock;
  
private: 
                              TriggerUnit(){;}
    TTrigger *                getTriggerPrivate( int id );
    void                      addTriggerRootNode( TTrigger * pT );
    void                      addTrigger( TTrigger * pT );
    void                      removeTriggerRootNode( TTrigger * pT );
    void                      removeTrigger( TTrigger *);
    
    Host *                    mpHost;
    QMap<int, TTrigger *>     mTriggerMap;
    std::list<TTrigger *>     mTriggerRootNodeList;

    qint64                    mMaxID;
   
   
};


#endif

