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

#ifndef DRUGINPUTEDIT_H
#define DRUGINPUTEDIT_H

#include <QTextEdit>
#include <QCompleter>
#include <QHash>
#include <QMouseEvent>

class DrugInputEdit : public QTextEdit
{
    Q_OBJECT
public:
    DrugInputEdit(QWidget *parent = 0);
    void setDrugList(QStringList modelList);

signals:
    void drugNameChanged(QString newWord);

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent * event);

public slots:
    void handleForceSuggest();
    void handleCompleteDrugName(QString addName);


private:
    QStringList _wordList;
    QCompleter _completer;


};

#endif // DRUGINPUTEDIT_H
