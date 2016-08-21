#ifndef libqmlrswrapper_H
#define libqmlrswrapper_H

#include <QtQuick>

typedef void *(QrsSlotFun)(const char *name, void *data, QVariant *result, QVariantList *args);

class QrsInterface;

class QrsApplicationEngine : public QQmlApplicationEngine {
    Q_OBJECT

public:
    QrsApplicationEngine();
};

#endif // libqmlrswrapper_H
