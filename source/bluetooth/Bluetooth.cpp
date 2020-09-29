//
//  Bluetooth.cpp
//  bluetooth
//
//  Created by Vladas Zakrevskis on 29/09/30.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#include <QMetaEnum>

#include <QtBluetooth/qbluetoothserviceinfo.h>
#include <QtBluetooth/qbluetoothuuid.h>
#include <QtBluetooth/qbluetoothdevicediscoveryagent.h>
#include <QtBluetooth/qbluetoothsocket.h>

#include "Log.hpp"
#include "Bluetooth.hpp"

using namespace bl;

class BTTest : QObject {

public:

    virtual ~BTTest() { }

Q_OBJECT

private slots:

    void channelReadyRead(int channel) { Log; };
    void bytesWritten(qint64 bytes) { Log; }
    void channelBytesWritten(int channel, qint64 bytes) { Log; }
    void aboutToClose() { Log; }
    void readChannelFinished() { Log; }
    void error(QBluetoothSocket::SocketError error) {
        QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketError>();
        Logvar(metaEnum.valueToKey(error)); };
    void stateChanged(QBluetoothSocket::SocketState state) {
        QMetaEnum metaEnum = QMetaEnum::fromType<QBluetoothSocket::SocketState>();
        Logvar(metaEnum.valueToKey(state)); }

    void connected() {
        Log;
        Logvar(socket->isOpen());
        Logvar(socket->isReadable());
        Logvar(socket->isWritable());
    };

    void disconnected() { Log; };

    void readyRead() {
        char data[1];
        Logvar(socket->bytesAvailable());
        socket->read(data, 1);
        Logvar((int)data[0]);
        Logvar(data[0]);
        Log;
    };

    void deviceDiscovered(const QBluetoothDeviceInfo &device) {
        Logvar(device.name());
        if (device.name() != "Glove") return;
        Logvar(device.address().toString());
        Logvar(device.deviceUuid().toString());
        std::optional<QBluetoothUuid> device_uuid;
        for (auto uuid : device.serviceUuids()) {
            device_uuid = uuid;
            Logvar(uuid.toString());
        }

        if (device_uuid->isNull()) {
            Fatal("Device uuid not found");
        }

        Logvar(device_uuid->toString());

        Log << "=======================";

//        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
//
//        socket->connectToService(device.address(),
//                //device.deviceUuid(),
//                //  device_uuid.value(),
//                                 QBluetoothUuid(QBluetoothUuid::SerialPort)
//                //QIODevice::ReadWrite
//        );
//
//        Logvar(socket->open(QIODevice::ReadWrite));
//
//        Log << "Connected?";
//
//        discoveryAgent->stop();
//
//        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
//        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
//        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
//        connect(socket, SIGNAL(stateChanged(QBluetoothSocket::SocketState)), this, SLOT(stateChanged(QBluetoothSocket::SocketState)));
//        connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SLOT(error(QBluetoothSocket::SocketError)));
//
//        connect(socket, SIGNAL(channelReadyRead(int)), this, SLOT(channelReadyRead(int)));
//        connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
//        connect(socket, SIGNAL(channelBytesWritten(int, qint64)), this, SLOT(channelBytesWritten(int, qint64)));
//        connect(socket, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
//        connect(socket, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));

    }


public:

    QBluetoothSocket* socket;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;

    void test() {
        discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
        connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)), this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
        discoveryAgent->start();
        Log << "Discovery start";
    }

};

static BTTest bt;


void Bluetooth::test() {
    Log;

    bt.test();

}

#include "Bluetooth.moc"
