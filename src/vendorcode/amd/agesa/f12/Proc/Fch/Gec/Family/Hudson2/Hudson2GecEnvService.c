/* $NoKeywords:$ */
/**
 * @file
 *
 * Config FCH GEC controller
 *
 * Init GEC features.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:     AGESA
 * @e sub-project: FCH
 * @e \$Revision: 46088 $   @e \$Date: 2011-01-28 11:24:26 +0800 (Fri, 28 Jan 2011) $
 *
 */
/*;********************************************************************************
;
* Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;*********************************************************************************/

#include "FchPlatform.h"
#include "Filecode.h"
#define FILECODE PROC_FCH_GEC_FAMILY_HUDSON2_HUDSON2GECENVSERVICE_FILECODE

/**
 * FchInitGecController - Config GEC controller
 *
 *
 *
 * @param[in] FchDataPtr Fch configuration structure pointer.
 *
 */
VOID
FchInitGecController (
  IN  VOID     *FchDataPtr
  )
{
  UINT8        FchSBGecDebugBus;
  UINT8        FchSBGecPwr;
  FCH_DATA_BLOCK         *LocalCfgPtr;

  LocalCfgPtr = (FCH_DATA_BLOCK *) FchDataPtr;

  FchSBGecDebugBus = (UINT8) LocalCfgPtr->Gec.GecDebugBus;
  FchSBGecPwr = (UINT8) LocalCfgPtr->Gec.GecPowerPolicy;

  if ( LocalCfgPtr->Misc.Cg2Pll == 1 ) {
    LocalCfgPtr->Gec.GecEnable = 1;
  }

  if ( LocalCfgPtr->Gec.GecEnable == 0) {
    //
    // GEC Enabled
    //
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGF6, AccessWidth8, ~BIT0, 0x00);
  } else {
    //
    // GEC Disabled
    //
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGF6, AccessWidth8, ~BIT0, BIT0);
    //return;                                                                              ///return if GEC controller is disabled.
  }

  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GEVENT_REG11, AccessWidth8, 0, 0x00);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GEVENT_REG21, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG166, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + IOMUX_BASE + FCH_GPIO_REG181, AccessWidth8, 0, 0x01);
  RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGF8, AccessWidth8, ~(BIT5 + BIT6), (UINT8) ((FchSBGecPwr) << 5));

  if (  FchSBGecDebugBus == 1) {
    //
    // GEC Debug Bus Enabled
    //
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGF6, AccessWidth8, ~BIT3, BIT3);
  } else {
    //
    // GEC Debug Bus Disabled
    //
    RwMem (ACPI_MMIO_BASE + PMIO_BASE + FCH_PMIOA_REGF6, AccessWidth8, ~BIT3, 0x00);
  }
}

