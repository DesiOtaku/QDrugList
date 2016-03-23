/*
 * (C) 2016 Tej A. Shah
 * This file is part of QDrugList

    QDrugList is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QDrugList is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QDrugList.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "druginputedit.h"

#include <QFile>
#include <QStringListModel>
#include <QDebug>
#include <QKeyEvent>
#include <QScrollBar>
#include <QAbstractItemView>

DrugInputEdit::DrugInputEdit(QWidget *parent) :
    QTextEdit(parent)
{
    _completer.setCompletionMode(QCompleter::PopupCompletion);
    _completer.setWidget(this);
    _completer.setCaseSensitivity(Qt::CaseInsensitive);
    connect(&_completer,SIGNAL(activated(QString)),this,SLOT(handleCompleteDrugName(QString)));
}

void DrugInputEdit::setDrugList(QStringList modelList) {
    _wordList = modelList;
    QStringListModel *model = new QStringListModel(_wordList,this);
    _completer.setModel(model);
    _completer.setModelSorting(QCompleter::UnsortedModel);
}

void DrugInputEdit::keyPressEvent(QKeyEvent *e) {

    if (_completer.popup()->isVisible()) {
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!isShortcut) // do not process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if ((ctrlOrShift && e->text().isEmpty()))
        return;

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    QString name = tc.selectedText();
    _completer.setCompletionPrefix(name);
    emit drugNameChanged(name);

    switch (e->key()) {
    case Qt::Key_Down:
    case Qt::Key_Up:
    case Qt::Key_Left:
    case Qt::Key_Right:
        return;
    default:
        break;
    }

    QRect cr = cursorRect();
    cr.setWidth(_completer.popup()->sizeHintForColumn(0)
                + _completer.popup()->verticalScrollBar()->sizeHint().width());
    _completer.complete(cr); // popup it up!

}

void DrugInputEdit::handleForceSuggest() {

}

void DrugInputEdit::handleCompleteDrugName(QString addName) {
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::LineUnderCursor);
    tc.removeSelectedText();
    tc.insertText(addName + "\n");
    setTextCursor(tc);
}


