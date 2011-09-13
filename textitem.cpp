
/****************************************************************************
**
** Copyright (C) 2007-2009 Kevin Clague. All rights reserved.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include "textitem.h"
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>

void TextItem::contextMenuEvent(
  QGraphicsSceneContextMenuEvent *event)
{
  QMenu menu;

  QAction *editFontAction = menu.addAction("Edit Font");
  editFontAction->setWhatsThis("Edit this text's font");

  QAction *editColorAction = menu.addAction("Edit Color");
  editColorAction->setWhatsThis("Edit this text's color");

  QAction *deleteTextAction = menu.addAction("Delete This Text");
  deleteTextAction->setWhatsThis("Delete this text");

  QAction *selectedAction  = menu.exec(event->screenPos());

  if (selectedAction == NULL) {
    return;
  }

  if (selectedAction == editFontAction) {

    QMessageBox::warning(NULL,
      QMessageBox::tr("LPub"),
      QMessageBox::tr("data = meta.value()"));

    InsertData data = meta._value;

    QMessageBox::warning(NULL,
      QMessageBox::tr("LPub"),
      QMessageBox::tr("font(data.textFont) %1") .arg(data.textFont));

    QFont font(data.textFont);
    bool ok;

    QMessageBox::warning(NULL,
      QMessageBox::tr("LPub"),
      QMessageBox::tr("getFont()"));

    font = QFontDialog::getFont(&ok,font);

    if (ok) {

      QMessageBox::warning(NULL,
        QMessageBox::tr("LPub"),
        QMessageBox::tr("font.toString()"));

      data.textFont = font.toString();

      QMessageBox::warning(NULL,
        QMessageBox::tr("LPub"),
        QMessageBox::tr("meta.setValue(data) %1") .arg(data.textFont));

      meta.setValue(data);

      QMessageBox::warning(NULL,
        QMessageBox::tr("LPub"),
        QMessageBox::tr("replaceMeta") .arg(data.textFont));

      beginMacro("UpdateFont");
      replaceMeta(meta.here(),meta.format(false,false));
      endMacro();
    } else {
      gui->displayPage();
    }
  } else if (selectedAction == editColorAction) {

    InsertData data = meta.value();

    QColor color(data.textColor);

    color = QColorDialog::getColor(color);

    data.textColor = color.name();
    meta.setValue(data);
    beginMacro("UpdateColor");
    replaceMeta(meta.here(),meta.format(false,false));
    endMacro();
  } else if (selectedAction == deleteTextAction) {

    Where here = meta.here();

    beginMacro("DeleteText");
    deleteMeta(here);
    endMacro();
  }
}


void TextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  position = pos();
  positionChanged = false;
  QGraphicsItem::mousePressEvent(event);
}

void TextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  positionChanged = true;
  QGraphicsItem::mouseMoveEvent(event);
}

void TextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem::mouseReleaseEvent(event);

  if (isSelected() && (flags() & QGraphicsItem::ItemIsMovable) && positionChanged) {

    InsertData insertData = meta.value();

    qreal topLeft[2] = { sceneBoundingRect().left(),  sceneBoundingRect().top() };
    qreal size[2]    = { sceneBoundingRect().width(), sceneBoundingRect().height() };

    PlacementData pld;

    pld.placement    = TopLeft;
    pld.justification    = Center;
    pld.relativeTo      = PageType;
    pld.preposition   = Inside;

    calcOffsets(pld,insertData.offsets,topLeft,size);
    insertData.text = toPlainText();

    meta.setValue(insertData);

    beginMacro(QString("MoveText"));

    changeInsertOffset(&meta);

    endMacro();
  }
}

void TextItem::focusInEvent(QFocusEvent *event)
{
  textChanged = false;
  QGraphicsTextItem::focusInEvent(event);
}
void TextItem::focusOutEvent(QFocusEvent *event)
{
  QGraphicsTextItem::focusOutEvent(event);
  // change meta

  if (textChanged) {
    InsertData insertData = meta.value();
    insertData.text = toPlainText();
    meta.setValue(insertData);

    beginMacro(QString("Edit"));
    changeInsertOffset(&meta);
    endMacro();
  }
}
void TextItem::keyPressEvent(QKeyEvent *event)
{
  textChanged = true;
  QGraphicsTextItem::keyPressEvent(event);
}
void TextItem::keyReleaseEvent(QKeyEvent *event)
{
  textChanged = true;
  QGraphicsTextItem::keyReleaseEvent(event);
}
