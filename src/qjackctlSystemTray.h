// qjackctlSystemTray.h
//
/****************************************************************************
   Copyright (C) 2003-2007, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __qjackctlSystemTray_h
#define __qjackctlSystemTray_h

#include <QWidget>
#include <QPixmap>
//Added by qt3to4:
#include <QPaintEvent>
#include <QMouseEvent>


//----------------------------------------------------------------------------
// qjackctlSystemTray -- Custom system tray widget.

class qjackctlSystemTray : public QWidget
{
	Q_OBJECT

public:

	// Constructor.
	qjackctlSystemTray(QWidget *pParent = 0);
	// Default destructor.
	~qjackctlSystemTray();

	// Background mask methods.
	void setBackground(const QColor& background);
	const QColor& background() const;

    // Set system tray icon overlay.
    void setPixmapOverlay(const QPixmap& pmOverlay);
	const QPixmap& pixmapOverlay() const;

	// System tray icon/pixmaps update method.
	void updateIcon();

signals:

	// Clicked signal.
	void clicked();

	// Context menu signal.
	void contextMenuRequested(const QPoint& pos);

protected:

	// Self-drawable methods.
	void paintEvent(QPaintEvent *);

	// Overriden mouse event method.
	void mousePressEvent(QMouseEvent *);

private:

	// Instance pixmap and background color.
	QPixmap m_pixmap;
	QPixmap m_pixmapOverlay;
	QColor  m_background;
};


#endif  // __qjackctlSystemTray_h

// end of qjackctlSystemTray.h
