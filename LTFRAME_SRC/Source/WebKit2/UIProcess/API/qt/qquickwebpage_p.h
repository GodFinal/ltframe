/*
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef qquickwebpage_p_h
#define qquickwebpage_p_h

#include "qwebkitglobal.h"

#include <QtCore/QSharedPointer>
#include <QtQuick/QQuickItem>

class QQuickWebPagePrivate;
class QQuickWebView;
class QtWebPageEventHandler;
class QWebPreferences;

namespace WebKit {
class QtSGUpdateQueue;
}

class QWEBKIT_EXPORT QQuickWebPage : public QQuickItem {
    Q_OBJECT
public:
    QQuickWebPage(QQuickWebView* view = 0);
    virtual ~QQuickWebPage();

    void setContentSize(const QSizeF& size);
    const QSizeF& contentSize() const;
    void setContentScale(qreal);
    qreal contentScale() const;

    QTransform transformFromItem() const;
    QTransform transformToItem() const;

    bool usesTraditionalDesktopBehaviour() const;
    void setUsesTraditionalDesktopBehaviour(bool enable);

    QtWebPageEventHandler* eventHandler() const;

    // Internal. To be removed soon.
    WebKit::QtSGUpdateQueue* sceneGraphUpdateQueue() const;

protected:
    virtual void geometryChanged(const QRectF&, const QRectF&);
    virtual QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*);

private:
    QQuickWebPagePrivate* d;
    friend class QQuickWebView;
    friend class QQuickWebViewPrivate;
};

QML_DECLARE_TYPE(QQuickWebPage)

#endif // qquickwebpage_p_h
