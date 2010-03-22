#include "osdep.h"
#include "kdebugprint.h"
#include "VIOSerialDriver.h"
#include "VIOSerialCoreControl.h"
#include "VIOSerialCoreQueue.h"

NTSTATUS SendControlMessage(PDEVICE_CONTEXT pContext,
							u32 uiPortID, // Control for this port
							u16 uiEvent, // Event 
							u16 uiValue) //Event related data
{
	VIRTIO_CONSOLE_CONTROL cpkt;

	DEBUG_ENTRY(0);
	//if (!use_multiport(port->portdev))
	//	return 0;

	cpkt.id = uiPortID;
	cpkt.event = uiEvent;
	cpkt.value = uiValue;

	DPrintf(0, ("Sending control>> Port: %d, event %d, value %d", uiPortID, uiEvent, uiValue));

	return VSCSendCopyBuffer(&pContext->SerialPorts[VIRTIO_SERIAL_CONTROL_PORT_INDEX], 
							 &cpkt, 
							 sizeof(VIRTIO_CONSOLE_CONTROL),
							 &pContext->DPCLock,
							 TRUE);
}
