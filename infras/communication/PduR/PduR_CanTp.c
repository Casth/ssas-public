/**
 * SSAS - Simple Smart Automotive Software
 * Copyright (C) 2022 Parai Wang <parai@foxmail.com>
 *
 * ref: Specification of PDU Router AUTOSAR CP Release 4.4.0
 */
/* ================================ [ INCLUDES  ] ============================================== */
#include "PduR.h"
#include "PduR_Priv.h"
#define PDUR_CANTP
#ifdef USE_LINTP
#include "LinTp_Cfg.h"
#endif
#include "PduR_CanTp.h"
/* ================================ [ MACROS    ] ============================================== */
#ifndef LINTP_GW_USER_HOOK_RX_IND
#define LINTP_GW_USER_HOOK_RX_IND(id, result)
#endif
/* ================================ [ TYPES     ] ============================================== */
/* ================================ [ DECLARES  ] ============================================== */
/* ================================ [ DATAS     ] ============================================== */
/* ================================ [ LOCALS    ] ============================================== */
/* ================================ [ FUNCTIONS ] ============================================== */
#if defined(PDUR_USE_MEMPOOL)
BufReq_ReturnType PduR_CanTpGwCopyTxData(PduIdType id, const PduInfoType *info,
                                         const RetryInfoType *retry,
                                         PduLengthType *availableDataPtr) {
  return PduR_GwCopyTxData(id, info, retry, availableDataPtr);
}

void PduR_CanTpGwTxConfirmation(PduIdType id, Std_ReturnType result) {
  PduR_GwTxConfirmation(id, result);
}

BufReq_ReturnType PduR_CanTpGwStartOfReception(PduIdType id, const PduInfoType *info,
                                               PduLengthType TpSduLength,
                                               PduLengthType *bufferSizePtr) {
  return PduR_GwStartOfReception(id, info, TpSduLength, bufferSizePtr);
}

BufReq_ReturnType PduR_CanTpGwCopyRxData(PduIdType id, const PduInfoType *info,
                                         PduLengthType *bufferSizePtr) {
  return PduR_GwCopyRxData(id, info, bufferSizePtr);
}

void PduR_CanTpGwRxIndication(PduIdType id, Std_ReturnType result) {
  LINTP_GW_USER_HOOK_RX_IND(id, result);
  PduR_GwRxIndication(id, result);
}
#endif
BufReq_ReturnType PduR_CanTpCopyTxData(PduIdType id, const PduInfoType *info,
                                       const RetryInfoType *retry,
                                       PduLengthType *availableDataPtr) {
  return PduR_CopyTxData(id + PDUR_CONFIG->cantpTxBaseID, info, retry, availableDataPtr);
}

void PduR_CanTpRxIndication(PduIdType id, Std_ReturnType result) {
  PduR_TpRxIndication(id + PDUR_CONFIG->cantpRxBaseID, result);
}

void PduR_CanTpTxConfirmation(PduIdType id, Std_ReturnType result) {
  PduR_TxConfirmation(id + PDUR_CONFIG->cantpTxBaseID, result);
}

BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType *info,
                                             PduLengthType TpSduLength,
                                             PduLengthType *bufferSizePtr) {
  return PduR_StartOfReception(id + PDUR_CONFIG->cantpRxBaseID, info, TpSduLength,
                               bufferSizePtr);
}

BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType *info,
                                       PduLengthType *bufferSizePtr) {
  return PduR_CopyRxData(id + PDUR_CONFIG->cantpRxBaseID, info, bufferSizePtr);
}
