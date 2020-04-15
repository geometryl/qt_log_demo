#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QMutex>

#include <stdio.h>
#include <stdlib.h>

#define LOG_DEBUG qDebug() << __FILE__ << " -- Line " << __LINE__ << ": "
#define LOG_INFO qInfo() << __FILE__ << " -- Line " << __LINE__ << ": "
#define LOG_WARNING qWarning() << __FILE__ << " -- Line " << __LINE__ << ": "
#define LOG_ERROR qCritical() << __FILE__ << " -- Line " << __LINE__ << ": "
#define LOG_FATAL qFatal() << __FILE__ << " -- Line " << __LINE__ << ": "

// print log
static void log_output(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    // current date time
    QDateTime dt = QDateTime::currentDateTime();
    // timestamp text
    QString content_dt = dt.toString("yyyy-MM-dd hh:mm:ss");
    // finally log text
    QString content_log;

    switch (type) {
    case QtDebugMsg:
        // if not debug mode, don't print debug log
#ifndef QT_NO_DEBUG
        content_log = QString("\033[37m[DEBUG %1] %2").arg(content_dt).arg(msg);
#endif
        break;
    case QtInfoMsg:
        content_log = QString("\033[32m[INFO %1] %2").arg(content_dt).arg(msg);
        break;
    case QtWarningMsg:
        content_log = QString("\033[33m[WARNING %1] %2").arg(content_dt).arg(msg);
        break;
    case QtCriticalMsg:
        content_log = QString("\033[31m[ERROR %1] %2").arg(content_dt).arg(msg);
        break;
    case QtFatalMsg:
        content_log = QString("\033[35m[FATAL %1] %2").arg(content_dt).arg(msg);
        break;
    default:
        break;
    }

    //    //    print log into.log file
    //    static QMutex mutex;
    //    mutex.lock(); // add lock for thread safety
    //    QFile file(QString("filename.log"));
    //    file.open(QIODevice::WriteOnly | QIODevice::Append); // add mode
    //    QTextStream text_stream(&file);
    //    text_stream.setCodec("UTF-8");
    //    text_stream << content_log << "\r\n";
    //    file.flush();
    //    file.close();
    //    mutex.unlock();//release lock
    fprintf(stderr, "%s\n", content_log.toLocal8Bit().constData());
    fflush(stdout);
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // register log output method
    qInstallMessageHandler(log_output);

    // DEBUG
    LOG_DEBUG << "debug log text.";
    LOG_INFO << "info log text.";
    LOG_WARNING << "warning log text";
    LOG_ERROR << "error log text";
    LOG_FATAL << "fatal log text";

    return app.exec();
}
