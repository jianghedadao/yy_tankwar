#ifndef CTANK_H
#define CTANK_H

#include <QObject>

class CTank : public QObject
{
    Q_OBJECT
public:
    explicit CTank(QObject *parent = nullptr);

signals:

};

#endif // CTANK_H
