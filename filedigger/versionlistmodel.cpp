/***************************************************************************
 *   Copyright Simon Persson                                               *
 *   simonpersson1@gmail.com                                               *
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

#include "versionlistmodel.h"
#include "../kioslave/vfshelpers.h"

#include <KMimeType>

VersionListModel::VersionListModel(QObject *parent) :
   QAbstractListModel(parent)
{
	mVersionList = NULL;
}

void VersionListModel::setNode(const MergedNode *pNode) {
	beginResetModel();
	mNode = pNode;
	mVersionList = mNode->versionList();
	endResetModel();
}

int VersionListModel::rowCount(const QModelIndex &pParent) const {
	Q_UNUSED(pParent)
	if(mVersionList != NULL) {
		return mVersionList->count();
	}
	return 0;
}

QVariant VersionListModel::data(const QModelIndex &pIndex, int pRole) const {
	if(!pIndex.isValid() || mVersionList == NULL) {
		return QVariant();
	}

	VersionData *lData = mVersionList->at(pIndex.row());
	switch (pRole) {
	case Qt::DisplayRole:
		return vfsTimeToString(lData->mModifiedDate);
	case VersionBupUrlRole:
		return mNode->getBupUrl(pIndex.row());
	case VersionMimeTypeRole:
		return KMimeType::findByUrl(mNode->objectName(), mNode->mode())->name();
	default:
		return QVariant();
	}
}