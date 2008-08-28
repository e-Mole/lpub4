
/****************************************************************************
**
** Copyright (C) 2007-2008 Kevin Clague. All rights reserved.
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

/****************************************************************************
 *
 * This file represents the page background and is derived from the generic
 * background class described in background.(h,cpp)
 *
 * Please see lpub.h for an overall description of how the files in LPub
 * make up the LPub program.
 *
 ***************************************************************************/

#include "pagebackgrounditem.h"
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QFileDialog>
#include "commonmenus.h"
#include "ranges_element.h"
#include "range.h"
#include "range_element.h"
#include "step.h"

void PageBackgroundItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
  QMenu menu;

  // figure out if first step step number is greater than 1

  QAction *addNextAction = NULL;

  Step    *lastStep = NULL;
  AbstractStepsElement *range = page->list[page->list.size()-1];
  if (range->relativeType == RangeType) {
    AbstractRangeElement *rangeElement = range->list[range->list.size()-1];
    if (rangeElement->relativeType == StepType) {
      lastStep = dynamic_cast<Step *> (rangeElement);
      MetaItem mi;
      int numSteps = mi.numSteps(lastStep->topOfStep().modelName);
      if (lastStep->stepNumber.number != numSteps) {
        addNextAction = menu.addAction("Add Next Step");
        addNextAction->setWhatsThis("Add Next Step:\n Add the first step of the next page to this page\n");
      }
    }
  }

  // figure out if first step step number is greater than 1

  QAction *addPrevAction = NULL;

  Step    *firstStep = NULL;
  range = page->list[0];
  if (range->relativeType == RangeType) {
    AbstractRangeElement *rangeElement = range->list[0];
    if (rangeElement->relativeType == StepType) {
      firstStep = dynamic_cast<Step *> (rangeElement);
      if (firstStep->stepNumber.number > 1) {
        addPrevAction = menu.addAction("Add Previous Step");
        addPrevAction->setWhatsThis("Add Previous Step:\n Add the last step of the previous page to this page\n");
      }
    }
  }

  QAction *calloutAction = NULL;
  QAction *ignoreAction = NULL;

  if (page->meta.submodelStack.size() > 0) {
    calloutAction = menu.addAction("Convert to Callout");
    calloutAction->setWhatsThis("Convert to Callout:\n"
      "  A callout shows how to build these steps in a picture next\n"
      "  to where it is added the the set you are building");
  
    ignoreAction  = menu.addAction("Ignore this submodel");
    ignoreAction->setWhatsThis("Stops these steps from showing up in your instructions");
  }

  QAction *selectedAction     = menu.exec(event->screenPos());

  if (selectedAction == NULL) {
    return;
  }

  if (selectedAction == calloutAction) {
    convertToCallout(&page->meta, page->bottom.modelName);

  } else if (selectedAction == ignoreAction) {
    convertToIgnore(&page->meta);

  } else if (selectedAction == addNextAction) {
    addNextMultiStep(lastStep->topOfSteps(),lastStep->bottomOfSteps());
  } else if (selectedAction == addPrevAction) {
    addPrevMultiStep(firstStep->topOfSteps(),firstStep->bottomOfSteps());
  }
}
