//
// Created by luks on 29.09.26.
//

#include "scpi-def.h"

scpi_t       scpi_context;
scpi_error_t scpi_error_queue_data[SCPI_ERROR_QUEUE_SIZE];

static scpi_result_t My_CoreTstQ(scpi_t *context);

const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    {
        .pattern  = "*CLS",
        .callback = SCPI_CoreCls,
    },
    {
        .pattern  = "*ESE",
        .callback = SCPI_CoreEse,
    },
    {
        .pattern  = "*ESE?",
        .callback = SCPI_CoreEseQ,
    },
    {
        .pattern  = "*ESR?",
        .callback = SCPI_CoreEsrQ,
    },
    {
        .pattern  = "*IDN?",
        .callback = SCPI_CoreIdnQ,
    },
    {
        .pattern  = "*OPC",
        .callback = SCPI_CoreOpc,
    },
    {
        .pattern  = "*OPC?",
        .callback = SCPI_CoreOpcQ,
    },
    {
        .pattern  = "*RST",
        .callback = SCPI_CoreRst,
    },
    {
        .pattern  = "*SRE",
        .callback = SCPI_CoreSre,
    },
    {
        .pattern  = "*SRE?",
        .callback = SCPI_CoreSreQ,
    },
    {
        .pattern  = "*STB?",
        .callback = SCPI_CoreStbQ,
    },
    {
        .pattern  = "*TST?",
        .callback = My_CoreTstQ,
    },
    {
        .pattern  = "*WAI",
        .callback = SCPI_CoreWai,
    },

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {
        .pattern  = "SYSTem:ERRor[:NEXT]?",
        .callback = SCPI_SystemErrorNextQ,
    },
    {
        .pattern  = "SYSTem:ERRor:COUNt?",
        .callback = SCPI_SystemErrorCountQ,
    },
    {
        .pattern  = "SYSTem:VERSion?",
        .callback = SCPI_SystemVersionQ,
    },

    /* {.pattern = "STATus:OPERation?", .callback = scpi_stub_callback,}, */
    /* {.pattern = "STATus:OPERation:EVENt?", .callback = scpi_stub_callback,},
     */
    /* {.pattern = "STATus:OPERation:CONDition?", .callback =
       scpi_stub_callback,}, */
    /* {.pattern = "STATus:OPERation:ENABle", .callback = scpi_stub_callback,},
     */
    /* {.pattern = "STATus:OPERation:ENABle?", .callback = scpi_stub_callback,},
     */

    {
        .pattern  = "STATus:QUEStionable[:EVENt]?",
        .callback = SCPI_StatusQuestionableEventQ,
    },
    /* {.pattern = "STATus:QUEStionable:CONDition?", .callback =
       scpi_stub_callback,}, */
    {
        .pattern  = "STATus:QUEStionable:ENABle",
        .callback = SCPI_StatusQuestionableEnable,
    },
    {
        .pattern  = "STATus:QUEStionable:ENABle?",
        .callback = SCPI_StatusQuestionableEnableQ,
    },

    {
        .pattern  = "STATus:PRESet",
        .callback = SCPI_StatusPreset,
    },

    /* DMM */
    /*{
        .pattern  = "MEASure:VOLTage:DC?",
        .callback = DMM_MeasureVoltageDcQ,
    },
    {
        .pattern  = "CONFigure:VOLTage:DC",
        .callback = DMM_ConfigureVoltageDc,
    },
    {
        .pattern  = "MEASure:VOLTage:DC:RATio?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:VOLTage:AC?",
        .callback = DMM_MeasureVoltageAcQ,
    },
    {
        .pattern  = "MEASure:CURRent:DC?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:CURRent:AC?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:RESistance?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:FRESistance?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:FREQuency?",
        .callback = SCPI_StubQ,
    },
    {
        .pattern  = "MEASure:PERiod?",
        .callback = SCPI_StubQ,
    },

    {
        .pattern  = "SYSTem:COMMunication:TCPIP:CONTROL?",
        .callback = SCPI_SystemCommTcpipControlQ,
    },

    {
        .pattern  = "TEST:BOOL",
        .callback = TEST_Bool,
    },
    {
        .pattern  = "TEST:CHOice?",
        .callback = TEST_ChoiceQ,
    },
    {
        .pattern  = "TEST#:NUMbers#",
        .callback = TEST_Numbers,
    },
    {
        .pattern  = "TEST:TEXT",
        .callback = TEST_Text,
    },
    {
        .pattern  = "TEST:ARBitrary?",
        .callback = TEST_ArbQ,
    },
    {
        .pattern  = "TEST:CHANnellist",
        .callback = TEST_Chanlst,
    },*/

    SCPI_CMD_LIST_END};

scpi_interface_t scpi_interface = {
    .error   = SCPI_Error,
    .write   = SCPI_Write,
    .control = SCPI_Control,
    .flush   = SCPI_Flush,
    .reset   = SCPI_Reset,
};

/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
static scpi_result_t My_CoreTstQ(scpi_t *context) {

  SCPI_ResultInt32(context, 0);

  return SCPI_RES_OK;
}