// qjackctlPatchbayRack.h
//
/****************************************************************************
   Copyright (C) 2003-2007, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __qjackctlPatchbayRack_h
#define __qjackctlPatchbayRack_h

#include "qjackctlAbout.h"

#include <QStringList>

#include <jack/jack.h>

#ifdef CONFIG_ALSA_SEQ
#include <alsa/asoundlib.h>
#else
typedef void snd_seq_t;
#endif

// Patchbay socket types.
#define QJACKCTL_SOCKETTYPE_AUDIO   0
#define QJACKCTL_SOCKETTYPE_MIDI    1

// Patchbay slot normalization modes.
#define QJACKCTL_SLOTMODE_OPEN      0
#define QJACKCTL_SLOTMODE_HALF      1
#define QJACKCTL_SLOTMODE_FULL      2

// Patchbay change signal flags.
#define QJACKCTL_CABLE_FAILED       0
#define QJACKCTL_CABLE_CHECKED      1
#define QJACKCTL_CABLE_CONNECTED    2
#define QJACKCTL_CABLE_DISCONNECTED 3


// Struct name says it all.
struct qjackctlMidiPort
{
	QString sClientName;
	QString sPortName;
	int iAlsaClient;
	int iAlsaPort;
};

// Patchbay socket definition.
class qjackctlPatchbaySocket
{
public:

	// Constructor.
	qjackctlPatchbaySocket(const QString& sSocketName, const QString& sClientName, int iSocketType);
	// Default destructor.
	~qjackctlPatchbaySocket();

	// Socket property accessors.
	const QString& name() const;
	const QString& clientName() const;
	int type() const;
	bool isExclusive() const;
	const QString& forward() const;

	// Socket property methods.
	void setName(const QString& sSocketName);
	void setClientName(const QString& sClientName);
	void setType(int iSocketType);
	void setExclusive(bool bExclusive);
	void setForward(const QString& sSocketForward);

	// Plug list primitive methods.
	void addPlug(const QString& sPlugName);
	void removePlug(const QString& sPlugName);

	// Plug list accessor.
	QStringList& pluglist();

private:

	// Properties.
	QString m_sSocketName;
	QString m_sClientName;
	int m_iSocketType;
	bool m_bExclusive;
	QString m_sSocketForward;

	// Patchbay socket plug list.
	QStringList m_pluglist;
};


// Patchbay socket slot definition.
class qjackctlPatchbaySlot
{
public:

	// Constructor.
	qjackctlPatchbaySlot(const QString& sSlotName, int iSlotMode = QJACKCTL_SLOTMODE_OPEN);
	// Default destructor.
	~qjackctlPatchbaySlot();

	// Slot property accessors.
	const QString& name() const;
	int mode() const;

	// Slot property methods.
	void setName(const QString& sSlotName);
	void setMode(int iSlotMode);

	// Socket methods.
	void setOutputSocket(qjackctlPatchbaySocket *pSocket);
	void setInputSocket(qjackctlPatchbaySocket *pSocket);

	// Socket accessors.
	qjackctlPatchbaySocket *outputSocket() const;
	qjackctlPatchbaySocket *inputSocket() const;

private:

	// Slot properties.
	QString m_sSlotName;
	int m_iSlotMode;

	// Socket references.
	qjackctlPatchbaySocket *m_pOutputSocket;
	qjackctlPatchbaySocket *m_pInputSocket;
};


// Patchbay cable connection definition.
class qjackctlPatchbayCable
{
public:

	// Constructor.
	qjackctlPatchbayCable(qjackctlPatchbaySocket *pOutputSocket,
		qjackctlPatchbaySocket *pInputSocket);
	// Default destructor.
	~qjackctlPatchbayCable();

	// Socket methods.
	void setOutputSocket(qjackctlPatchbaySocket *pSocket);
	void setInputSocket(qjackctlPatchbaySocket *pSocket);

	// Socket accessors.
	qjackctlPatchbaySocket *outputSocket() const;
	qjackctlPatchbaySocket *inputSocket() const;

private:

	// Socket references.
	qjackctlPatchbaySocket *m_pOutputSocket;
	qjackctlPatchbaySocket *m_pInputSocket;
};


// Patchbay rack profile definition.
class qjackctlPatchbayRack : public QObject
{
	Q_OBJECT

public:

	// Constructor.
	qjackctlPatchbayRack();
	// Default destructor.
	~qjackctlPatchbayRack();

	// Common socket list primitive methods.
	void addSocket(QList<qjackctlPatchbaySocket *>& socketlist,
		qjackctlPatchbaySocket *pSocket);
	void removeSocket(QList<qjackctlPatchbaySocket *>& socketlist,
		qjackctlPatchbaySocket *pSocket);

	// Slot list primitive methods.
	void addSlot(qjackctlPatchbaySlot *pSlot);
	void removeSlot(qjackctlPatchbaySlot *pSlot);

	// Cable list primitive methods.
	void addCable(qjackctlPatchbayCable *pCable);
	void removeCable(qjackctlPatchbayCable *pCable);

	// Common socket finder.
	qjackctlPatchbaySocket *findSocket(
		QList<qjackctlPatchbaySocket *>& socketlist, const QString& sSocketName);
	// Slot finders.
	qjackctlPatchbaySlot *findSlot(const QString& sSlotName);
	// Cable finder.
	qjackctlPatchbayCable *findCable(
		const QString& sOutputSocket, const QString& sInputSocket);
	qjackctlPatchbayCable *findCable(qjackctlPatchbayCable *pCablePtr);

	// Patchbay cleaner.
	void clear();

	// Patchbay rack socket list accessors.
	QList<qjackctlPatchbaySocket *>& osocketlist();
	QList<qjackctlPatchbaySocket *>& isocketlist();
	// Patchbay rack slots list accessor.
	QList<qjackctlPatchbaySlot *>& slotlist();
	// Patchbay cable connections list accessor.
	QList<qjackctlPatchbayCable *>& cablelist();

	// Overloaded cable connection persistence scan cycle methods.
	void connectAudioScan(jack_client_t *pJackClient);
	void connectMidiScan(snd_seq_t *pAlsaSeq);

signals:

	// Cable connection change signal.
	void cableConnected(const QString& sOutputPort,
		const QString& sInputPort, unsigned int uiCableFlags);

private:

	// Audio connection scan related private methods.
	const char *findAudioPort(const char **ppszClientPorts,
		const QString& sClientName, const QString& sPortName, int n = 0);
	void connectAudioPorts(
		const char *pszOutputPort, const char *pszInputPort);
	void disconnectAudioPorts(
		const char *pszOutputPort, const char *pszInputPort);
	void checkAudioPorts(
		const char *pszOutputPort, const char *pszInputPort);
	void connectAudioSocketPorts(
		qjackctlPatchbaySocket *pOutputSocket, const char *pszOutputPort,
		qjackctlPatchbaySocket *pInputSocket, const char *pszInputPort);
	void connectAudioCable(
		qjackctlPatchbaySocket *pOutputSocket,
		qjackctlPatchbaySocket *pInputSocket);

	// MIDI connection scan related private methods.
	void loadMidiPorts(QList<qjackctlMidiPort *>& midiports, bool bReadable);
	qjackctlMidiPort *findMidiPort (QList<qjackctlMidiPort *>& midiports,
		const QString& sClientName, const QString& sPortName, int n);
	QString getMidiPortName(qjackctlMidiPort *pMidiPort);
	void setMidiPort(qjackctlMidiPort *pMidiPort,
		int iAlsaClient, int iAlsaPort);
	void connectMidiPorts(
		qjackctlMidiPort *pOutputPort, qjackctlMidiPort *pInputPort);
	void disconnectMidiPorts(
		qjackctlMidiPort *pOutputPort, qjackctlMidiPort *pInputPort);
	void checkMidiPorts(
		qjackctlMidiPort *pOutputPort, qjackctlMidiPort *pInputPort);
	void connectMidiSocketPorts(
		qjackctlPatchbaySocket *pOutputSocket, qjackctlMidiPort *pOutputPort,
		qjackctlPatchbaySocket *pInputSocket, qjackctlMidiPort *pInputPort);
	void connectMidiCable(
		qjackctlPatchbaySocket *pOutputSocket,
		qjackctlPatchbaySocket *pInputSocket);

	void loadMidiConnections(QList<qjackctlMidiPort *>& midiports,
		qjackctlMidiPort *pMidiPort, bool bReadable);

	// Audio socket/ports forwarding executive methods.
	void connectAudioForwardPorts(
		const char *pszPort, const char *pszPortForward);
	void connectAudioForward(
		qjackctlPatchbaySocket *pSocket,
		qjackctlPatchbaySocket *pSocketForward);

	// MIDI socket/ports forwarding executive methods.
	void connectMidiForwardPorts(
		qjackctlMidiPort *pPort, qjackctlMidiPort *pPortForward);
	void connectMidiForward(
		qjackctlPatchbaySocket *pSocket,
		qjackctlPatchbaySocket *pSocketForward);

	// Common socket forwarding scan method.
	void connectForwardScan(int iSocketType);

	// Patchbay sockets lists.
	QList<qjackctlPatchbaySocket *> m_osocketlist;
	QList<qjackctlPatchbaySocket *> m_isocketlist;
	// Patchbay rack slots list.
	QList<qjackctlPatchbaySlot *> m_slotlist;
	// Patchbay cable connections list.
	QList<qjackctlPatchbayCable *> m_cablelist;

	// Audio connection persistence cache variables.
	jack_client_t *m_pJackClient;
	const char **m_ppszOAudioPorts;
	const char **m_ppszIAudioPorts;

	// MIDI connection persistence cache variables.
	snd_seq_t *m_pAlsaSeq;
	QList<qjackctlMidiPort *> m_omidiports;
	QList<qjackctlMidiPort *> m_imidiports;
};


#endif  // __qjackctlPatchbayRack_h

// qjackctlPatchbayRack.h
