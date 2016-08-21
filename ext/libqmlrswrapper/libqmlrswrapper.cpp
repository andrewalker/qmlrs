#include "libqmlrswrapper.h"

#include "qrsdynamicobject.h"

#include <QtQuick>
#include <QDebug>
#include <sailfishapp.h>

#define rust_fun extern "C"

QGuiApplication *singleton_gui_app;
QQuickView *singleton_view;

rust_fun QrsApplicationEngine *qmlrs_create_engine() {
    if (!singleton_gui_app) {
        char *arg = (char *)malloc(13);
        strcpy(arg, "qmlrswrapper");
        char **argp = (char **)malloc(sizeof(char *));
        *argp = arg;

        int *argc = (int *)malloc(sizeof(int));
        *argc = 1;

        singleton_gui_app = SailfishApp::application(*argc, argp);
    }

    return new QrsApplicationEngine();
}

rust_fun void qmlrs_create_view(const char *path, uint len) {
    singleton_view = SailfishApp::createView();

    QString qml = QString::fromUtf8(path, len);
    singleton_view->setSource(QUrl::fromLocalFile(qml));
    singleton_view->show();

    QObject::connect(singleton_view->engine(), &QQmlEngine::quit, singleton_gui_app, &QGuiApplication::quit);

    return;
}

rust_fun void qmlrs_destroy_engine(QrsApplicationEngine *engine) {
    delete engine;
}

rust_fun void qmlrs_engine_set_property(QrsApplicationEngine *engine, const char *name, uint len,
                                        QObject *object) {
    singleton_view->rootContext()->setContextProperty(QString::fromUtf8(name, len), object);
}

rust_fun QVariantList *qmlrs_varlist_create() {
    return new QVariantList();
}

rust_fun void qmlrs_varlist_destroy(QVariantList *list) {
    delete list;
}

rust_fun QVariant *qmlrs_varlist_push(QVariantList *list) {
    list->append(QVariant());
    return (QVariant *)&list->last();
}

rust_fun unsigned int qmlrs_varlist_length(const QVariantList *list) {
    return list->size();
}

rust_fun QVariant *qmlrs_varlist_get(const QVariantList *list, unsigned int i) {
    return (QVariant *)&(*list)[i];
}

rust_fun void qmlrs_app_exec() {
    singleton_gui_app->exec();
}

rust_fun void qmlrs_variant_set_int64(QVariant *v, int64_t x) {
    *v = QVariant((qlonglong)x);
}

rust_fun void qmlrs_variant_set_bool(QVariant *v, bool x) {
    *v = QVariant(x);
}

rust_fun void qmlrs_variant_set_invalid(QVariant *v) {
    *v = QVariant();
}

rust_fun void qmlrs_variant_set_string(QVariant *v, unsigned int len, const char *data) {
    *v = QVariant(QString::fromUtf8(data, len));
}

rust_fun QVariant *qmlrs_variant_create() {
    return new QVariant();
}

rust_fun void qmlrs_variant_destroy(QVariant *v) {
    delete v;
}

enum QrsVariantType {
    Invalid = 0, Int64, Bool, String
};

rust_fun QrsVariantType qmlrs_variant_get_type(const QVariant *v) {
    if (!v->isValid())
        return Invalid;

    if (v->type() == (QVariant::Type)QMetaType::QString)
        return String;

    if (v->canConvert(QMetaType::LongLong))
        return Int64;

    if (v->canConvert(QMetaType::Bool))
        return Bool;

    /* Unknown type, not supported on Rust side */
    return Invalid;
}

rust_fun void qmlrs_variant_get_int64(const QVariant *v, int64_t *x) {
    *x = v->toLongLong();
}

rust_fun void qmlrs_variant_get_bool(const QVariant *v, bool *x) {
    *x = v->toBool();
}

rust_fun void qmlrs_variant_get_string_length(const QVariant *v, unsigned int *len) {
    *len = v->toString().toUtf8().size();
}

rust_fun void qmlrs_variant_get_string_data(const QVariant *v, char *data) {
    QByteArray ba = v->toString().toUtf8();
    memcpy(data, ba.data(), ba.size());
}

QrsApplicationEngine::QrsApplicationEngine()
{
}
