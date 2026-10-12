/* Utopia W65C816 Static Dispatch - Generated */
#include "ut_v11_runtime.h"
#include "ut_v11_cpu.h"
#include "ut_static_helpers.h"
#include <stdint.h>

/* Forward declarations */
static void bb_00_2020(SCV11Runtime* runtime);
static void bb_00_2025(SCV11Runtime* runtime);
static void bb_00_202D(SCV11Runtime* runtime);
static void bb_00_2035(SCV11Runtime* runtime);
static void bb_00_203A(SCV11Runtime* runtime);
static void bb_00_203F(SCV11Runtime* runtime);
static void bb_00_204A(SCV11Runtime* runtime);
static void bb_00_204F(SCV11Runtime* runtime);
static void bb_00_2057(SCV11Runtime* runtime);
static void bb_00_205F(SCV11Runtime* runtime);
static void bb_00_2061(SCV11Runtime* runtime);
static void bb_00_2063(SCV11Runtime* runtime);
static void bb_00_2065(SCV11Runtime* runtime);
static void bb_00_2067(SCV11Runtime* runtime);
static void bb_00_2069(SCV11Runtime* runtime);
static void bb_00_206B(SCV11Runtime* runtime);
static void bb_00_206D(SCV11Runtime* runtime);
static void bb_00_206F(SCV11Runtime* runtime);
static void bb_00_2071(SCV11Runtime* runtime);
static void bb_00_2073(SCV11Runtime* runtime);
static void bb_00_2075(SCV11Runtime* runtime);
static void bb_00_2077(SCV11Runtime* runtime);
static void bb_00_2079(SCV11Runtime* runtime);
static void bb_00_207B(SCV11Runtime* runtime);
static void bb_00_207D(SCV11Runtime* runtime);
static void bb_00_207F(SCV11Runtime* runtime);
static void bb_00_2087(SCV11Runtime* runtime);
static void bb_00_208F(SCV11Runtime* runtime);
static void bb_00_2091(SCV11Runtime* runtime);
static void bb_00_2093(SCV11Runtime* runtime);
static void bb_00_2095(SCV11Runtime* runtime);
static void bb_00_2097(SCV11Runtime* runtime);
static void bb_00_2099(SCV11Runtime* runtime);
static void bb_00_209B(SCV11Runtime* runtime);
static void bb_00_209D(SCV11Runtime* runtime);
static void bb_00_7FC2(SCV11Runtime* runtime);
static void bb_00_7FC4(SCV11Runtime* runtime);
static void bb_00_7FC6(SCV11Runtime* runtime);
static void bb_00_800C(SCV11Runtime* runtime);
static void bb_00_800F(SCV11Runtime* runtime);
static void bb_00_8010(SCV11Runtime* runtime);
static void bb_00_8011(SCV11Runtime* runtime);
static void bb_00_8012(SCV11Runtime* runtime);
static void bb_00_8013(SCV11Runtime* runtime);
static void bb_00_8015(SCV11Runtime* runtime);
static void bb_00_8016(SCV11Runtime* runtime);
static void bb_00_8017(SCV11Runtime* runtime);
static void bb_00_8018(SCV11Runtime* runtime);
static void bb_00_8019(SCV11Runtime* runtime);
static void bb_00_801C(SCV11Runtime* runtime);
static void bb_00_801F(SCV11Runtime* runtime);
static void bb_00_8020(SCV11Runtime* runtime);
static void bb_00_8022(SCV11Runtime* runtime);
static void bb_00_8024(SCV11Runtime* runtime);
static void bb_00_8025(SCV11Runtime* runtime);
static void bb_00_8026(SCV11Runtime* runtime);
static void bb_00_8031(SCV11Runtime* runtime);
static void bb_00_8033(SCV11Runtime* runtime);
static void bb_00_81A2(SCV11Runtime* runtime);
static void bb_00_81A7(SCV11Runtime* runtime);
static void bb_00_81AA(SCV11Runtime* runtime);
static void bb_00_81AB(SCV11Runtime* runtime);
static void bb_00_81AC(SCV11Runtime* runtime);
static void bb_00_81AD(SCV11Runtime* runtime);
static void bb_00_81AE(SCV11Runtime* runtime);
static void bb_00_81B0(SCV11Runtime* runtime);
static void bb_00_81B1(SCV11Runtime* runtime);
static void bb_00_81B2(SCV11Runtime* runtime);
static void bb_00_81B3(SCV11Runtime* runtime);
static void bb_00_81B4(SCV11Runtime* runtime);
static void bb_00_81B7(SCV11Runtime* runtime);
static void bb_00_81BC(SCV11Runtime* runtime);
static void bb_00_81BD(SCV11Runtime* runtime);
static void bb_00_81BE(SCV11Runtime* runtime);
static void bb_00_81C0(SCV11Runtime* runtime);
static void bb_00_81C1(SCV11Runtime* runtime);
static void bb_00_81C6(SCV11Runtime* runtime);
static void bb_00_81C7(SCV11Runtime* runtime);
static void bb_00_81C9(SCV11Runtime* runtime);
static void bb_00_81CA(SCV11Runtime* runtime);
static void bb_00_81D0(SCV11Runtime* runtime);
static void bb_00_81D6(SCV11Runtime* runtime);
static void bb_00_81DC(SCV11Runtime* runtime);
static void bb_00_81DF(SCV11Runtime* runtime);
static void bb_00_81E2(SCV11Runtime* runtime);
static void bb_00_81E3(SCV11Runtime* runtime);
static void bb_00_81E6(SCV11Runtime* runtime);
static void bb_00_81E9(SCV11Runtime* runtime);
static void bb_00_81EC(SCV11Runtime* runtime);
static void bb_00_81EE(SCV11Runtime* runtime);
static void bb_00_81EF(SCV11Runtime* runtime);
static void bb_00_81F0(SCV11Runtime* runtime);
static void bb_00_82B7(SCV11Runtime* runtime);
static void bb_00_82B8(SCV11Runtime* runtime);
static void bb_00_82B9(SCV11Runtime* runtime);
static void bb_00_82BC(SCV11Runtime* runtime);
static void bb_00_82BD(SCV11Runtime* runtime);
static void bb_00_82C0(SCV11Runtime* runtime);
static void bb_00_82C3(SCV11Runtime* runtime);
static void bb_00_82C4(SCV11Runtime* runtime);
static void bb_00_82C6(SCV11Runtime* runtime);
static void bb_00_82C9(SCV11Runtime* runtime);
static void bb_00_82CB(SCV11Runtime* runtime);
static void bb_00_82CC(SCV11Runtime* runtime);
static void bb_00_82CD(SCV11Runtime* runtime);
static void bb_00_82CF(SCV11Runtime* runtime);
static void bb_00_82D0(SCV11Runtime* runtime);
static void bb_00_82D1(SCV11Runtime* runtime);
static void bb_00_82D2(SCV11Runtime* runtime);
static void bb_00_82D3(SCV11Runtime* runtime);
static void bb_00_82D4(SCV11Runtime* runtime);
static void bb_01_8141(SCV11Runtime* runtime);
static void bb_01_8142(SCV11Runtime* runtime);
static void bb_01_8145(SCV11Runtime* runtime);
static void bb_01_8148(SCV11Runtime* runtime);
static void bb_01_814E(SCV11Runtime* runtime);
static void bb_01_8151(SCV11Runtime* runtime);
static void bb_01_8154(SCV11Runtime* runtime);
static void bb_01_8159(SCV11Runtime* runtime);
static void bb_01_815A(SCV11Runtime* runtime);
static void bb_01_815D(SCV11Runtime* runtime);
static void bb_01_8160(SCV11Runtime* runtime);
static void bb_01_8166(SCV11Runtime* runtime);
static void bb_01_8168(SCV11Runtime* runtime);
static void bb_01_816E(SCV11Runtime* runtime);
static void bb_01_8173(SCV11Runtime* runtime);
static void bb_01_8174(SCV11Runtime* runtime);
static void bb_01_8179(SCV11Runtime* runtime);
static void bb_01_817A(SCV11Runtime* runtime);
static void bb_01_817D(SCV11Runtime* runtime);
static void bb_01_8180(SCV11Runtime* runtime);
static void bb_01_8183(SCV11Runtime* runtime);
static void bb_01_8185(SCV11Runtime* runtime);
static void bb_01_818A(SCV11Runtime* runtime);
static void bb_01_818D(SCV11Runtime* runtime);
static void bb_01_818E(SCV11Runtime* runtime);
static void bb_01_81A7(SCV11Runtime* runtime);
static void bb_01_81A9(SCV11Runtime* runtime);
static void bb_01_81AA(SCV11Runtime* runtime);
static void bb_01_81AD(SCV11Runtime* runtime);
static void bb_01_81B1(SCV11Runtime* runtime);
static void bb_01_81B2(SCV11Runtime* runtime);
static void bb_01_81B3(SCV11Runtime* runtime);
static void bb_01_81EA(SCV11Runtime* runtime);
static void bb_01_81F0(SCV11Runtime* runtime);
static void bb_01_81F6(SCV11Runtime* runtime);
static void bb_01_81FC(SCV11Runtime* runtime);
static void bb_01_8202(SCV11Runtime* runtime);
static void bb_01_8203(SCV11Runtime* runtime);
static void bb_01_8204(SCV11Runtime* runtime);
static void bb_01_8205(SCV11Runtime* runtime);
static void bb_01_8206(SCV11Runtime* runtime);
static void bb_01_8209(SCV11Runtime* runtime);
static void bb_01_820A(SCV11Runtime* runtime);
static void bb_01_820B(SCV11Runtime* runtime);
static void bb_01_820C(SCV11Runtime* runtime);
static void bb_01_820D(SCV11Runtime* runtime);
static void bb_01_820E(SCV11Runtime* runtime);
static void bb_01_8211(SCV11Runtime* runtime);
static void bb_01_8212(SCV11Runtime* runtime);
static void bb_01_8215(SCV11Runtime* runtime);
static void bb_01_8219(SCV11Runtime* runtime);
static void bb_01_821A(SCV11Runtime* runtime);
static void bb_01_821B(SCV11Runtime* runtime);
static void bb_01_821C(SCV11Runtime* runtime);
static void bb_01_821D(SCV11Runtime* runtime);
static void bb_01_821E(SCV11Runtime* runtime);
static void bb_01_821F(SCV11Runtime* runtime);
static void bb_01_8220(SCV11Runtime* runtime);
static void bb_01_8221(SCV11Runtime* runtime);
static void bb_01_8222(SCV11Runtime* runtime);
static void bb_01_8223(SCV11Runtime* runtime);
static void bb_01_8224(SCV11Runtime* runtime);
static void bb_01_8225(SCV11Runtime* runtime);
static void bb_01_8226(SCV11Runtime* runtime);
static void bb_01_8227(SCV11Runtime* runtime);
static void bb_01_8228(SCV11Runtime* runtime);
static void bb_01_8229(SCV11Runtime* runtime);
static void bb_01_822A(SCV11Runtime* runtime);
static void bb_01_822B(SCV11Runtime* runtime);
static void bb_01_822C(SCV11Runtime* runtime);
static void bb_01_822D(SCV11Runtime* runtime);
static void bb_01_822E(SCV11Runtime* runtime);
static void bb_01_822F(SCV11Runtime* runtime);
static void bb_01_8230(SCV11Runtime* runtime);
static void bb_01_8231(SCV11Runtime* runtime);
static void bb_01_8232(SCV11Runtime* runtime);
static void bb_01_8233(SCV11Runtime* runtime);
static void bb_01_8234(SCV11Runtime* runtime);
static void bb_01_8235(SCV11Runtime* runtime);
static void bb_01_8236(SCV11Runtime* runtime);
static void bb_01_8237(SCV11Runtime* runtime);
static void bb_01_8238(SCV11Runtime* runtime);
static void bb_01_8239(SCV11Runtime* runtime);
static void bb_01_823A(SCV11Runtime* runtime);
static void bb_01_823B(SCV11Runtime* runtime);
static void bb_01_823C(SCV11Runtime* runtime);
static void bb_01_823D(SCV11Runtime* runtime);
static void bb_01_823E(SCV11Runtime* runtime);
static void bb_01_823F(SCV11Runtime* runtime);
static void bb_01_8240(SCV11Runtime* runtime);
static void bb_01_8241(SCV11Runtime* runtime);
static void bb_01_8242(SCV11Runtime* runtime);
static void bb_01_8243(SCV11Runtime* runtime);
static void bb_01_8244(SCV11Runtime* runtime);
static void bb_01_8245(SCV11Runtime* runtime);
static void bb_01_8246(SCV11Runtime* runtime);
static void bb_01_8247(SCV11Runtime* runtime);
static void bb_01_8248(SCV11Runtime* runtime);
static void bb_01_8249(SCV11Runtime* runtime);
static void bb_01_824A(SCV11Runtime* runtime);
static void bb_01_824B(SCV11Runtime* runtime);
static void bb_01_824C(SCV11Runtime* runtime);
static void bb_01_824D(SCV11Runtime* runtime);
static void bb_01_824E(SCV11Runtime* runtime);
static void bb_01_824F(SCV11Runtime* runtime);
static void bb_01_8250(SCV11Runtime* runtime);
static void bb_01_8251(SCV11Runtime* runtime);
static void bb_01_8252(SCV11Runtime* runtime);
static void bb_01_8253(SCV11Runtime* runtime);
static void bb_01_8254(SCV11Runtime* runtime);
static void bb_01_8255(SCV11Runtime* runtime);
static void bb_01_8256(SCV11Runtime* runtime);
static void bb_01_8257(SCV11Runtime* runtime);
static void bb_01_8258(SCV11Runtime* runtime);
static void bb_01_8259(SCV11Runtime* runtime);
static void bb_01_825A(SCV11Runtime* runtime);
static void bb_01_825B(SCV11Runtime* runtime);
static void bb_01_825C(SCV11Runtime* runtime);
static void bb_01_825D(SCV11Runtime* runtime);
static void bb_01_825E(SCV11Runtime* runtime);
static void bb_01_825F(SCV11Runtime* runtime);
static void bb_01_8260(SCV11Runtime* runtime);
static void bb_01_8261(SCV11Runtime* runtime);
static void bb_01_8262(SCV11Runtime* runtime);
static void bb_01_8263(SCV11Runtime* runtime);
static void bb_01_8264(SCV11Runtime* runtime);
static void bb_01_8266(SCV11Runtime* runtime);
static void bb_01_8268(SCV11Runtime* runtime);
static void bb_01_8269(SCV11Runtime* runtime);
static void bb_01_826A(SCV11Runtime* runtime);
static void bb_01_826C(SCV11Runtime* runtime);
static void bb_01_826E(SCV11Runtime* runtime);
static void bb_01_826F(SCV11Runtime* runtime);
static void bb_01_8270(SCV11Runtime* runtime);
static void bb_01_8272(SCV11Runtime* runtime);
static void bb_01_8274(SCV11Runtime* runtime);
static void bb_01_8277(SCV11Runtime* runtime);
static void bb_01_827B(SCV11Runtime* runtime);
static void bb_01_827C(SCV11Runtime* runtime);
static void bb_01_827D(SCV11Runtime* runtime);
static void bb_01_827E(SCV11Runtime* runtime);
static void bb_01_827F(SCV11Runtime* runtime);
static void bb_01_8280(SCV11Runtime* runtime);
static void bb_01_8281(SCV11Runtime* runtime);
static void bb_01_8282(SCV11Runtime* runtime);
static void bb_01_8283(SCV11Runtime* runtime);
static void bb_01_8284(SCV11Runtime* runtime);
static void bb_01_8285(SCV11Runtime* runtime);
static void bb_01_8286(SCV11Runtime* runtime);
static void bb_01_8287(SCV11Runtime* runtime);
static void bb_01_8288(SCV11Runtime* runtime);
static void bb_01_8289(SCV11Runtime* runtime);
static void bb_01_828A(SCV11Runtime* runtime);
static void bb_01_828B(SCV11Runtime* runtime);
static void bb_01_828C(SCV11Runtime* runtime);
static void bb_01_828F(SCV11Runtime* runtime);
static void bb_01_8290(SCV11Runtime* runtime);
static void bb_01_8291(SCV11Runtime* runtime);
static void bb_01_8292(SCV11Runtime* runtime);
static void bb_01_8293(SCV11Runtime* runtime);
static void bb_01_8294(SCV11Runtime* runtime);
static void bb_01_8295(SCV11Runtime* runtime);
static void bb_01_8296(SCV11Runtime* runtime);
static void bb_01_8298(SCV11Runtime* runtime);
static void bb_01_829A(SCV11Runtime* runtime);
static void bb_01_829C(SCV11Runtime* runtime);
static void bb_01_829F(SCV11Runtime* runtime);
static void bb_01_82A0(SCV11Runtime* runtime);
static void bb_01_82A1(SCV11Runtime* runtime);
static void bb_01_82A2(SCV11Runtime* runtime);
static void bb_01_82A3(SCV11Runtime* runtime);
static void bb_01_82A4(SCV11Runtime* runtime);
static void bb_01_82A5(SCV11Runtime* runtime);
static void bb_01_82A6(SCV11Runtime* runtime);
static void bb_01_82A7(SCV11Runtime* runtime);
static void bb_01_82A8(SCV11Runtime* runtime);
static void bb_01_82AB(SCV11Runtime* runtime);
static void bb_01_82B1(SCV11Runtime* runtime);
static void bb_01_82B3(SCV11Runtime* runtime);
static void bb_01_82B5(SCV11Runtime* runtime);
static void bb_01_82B6(SCV11Runtime* runtime);
static void bb_01_82B7(SCV11Runtime* runtime);
static void bb_01_82B8(SCV11Runtime* runtime);
static void bb_01_82B9(SCV11Runtime* runtime);
static void bb_01_82BA(SCV11Runtime* runtime);
static void bb_01_82BB(SCV11Runtime* runtime);
static void bb_01_82BC(SCV11Runtime* runtime);
static void bb_01_82BD(SCV11Runtime* runtime);
static void bb_01_82BE(SCV11Runtime* runtime);
static void bb_01_82BF(SCV11Runtime* runtime);
static void bb_01_82C0(SCV11Runtime* runtime);
static void bb_01_82C1(SCV11Runtime* runtime);
static void bb_01_82C2(SCV11Runtime* runtime);
static void bb_01_82C3(SCV11Runtime* runtime);
static void bb_01_82C4(SCV11Runtime* runtime);
static void bb_01_82C7(SCV11Runtime* runtime);
static void bb_01_82CA(SCV11Runtime* runtime);
static void bb_02_81A2(SCV11Runtime* runtime);
static void bb_02_81A3(SCV11Runtime* runtime);
static void bb_02_81A4(SCV11Runtime* runtime);
static void bb_02_81A7(SCV11Runtime* runtime);
static void bb_02_81A8(SCV11Runtime* runtime);
static void bb_02_81A9(SCV11Runtime* runtime);
static void bb_02_81AB(SCV11Runtime* runtime);
static void bb_02_81AC(SCV11Runtime* runtime);
static void bb_02_81AF(SCV11Runtime* runtime);
static void bb_02_81B0(SCV11Runtime* runtime);
static void bb_02_81B1(SCV11Runtime* runtime);
static void bb_02_81B2(SCV11Runtime* runtime);
static void bb_02_81B3(SCV11Runtime* runtime);
static void bb_02_81B4(SCV11Runtime* runtime);
static void bb_02_81B5(SCV11Runtime* runtime);
static void bb_02_81B6(SCV11Runtime* runtime);
static void bb_02_81B7(SCV11Runtime* runtime);
static void bb_02_81B8(SCV11Runtime* runtime);
static void bb_02_81B9(SCV11Runtime* runtime);
static void bb_02_81BB(SCV11Runtime* runtime);
static void bb_02_81BC(SCV11Runtime* runtime);
static void bb_02_81BE(SCV11Runtime* runtime);
static void bb_02_81C1(SCV11Runtime* runtime);
static void bb_07_800C(SCV11Runtime* runtime);
static void bb_07_800D(SCV11Runtime* runtime);
static void bb_07_800E(SCV11Runtime* runtime);
static void bb_07_8010(SCV11Runtime* runtime);
static void bb_07_82B7(SCV11Runtime* runtime);
static void bb_07_8319(SCV11Runtime* runtime);
static void bb_07_831A(SCV11Runtime* runtime);
static void bb_0C_8177(SCV11Runtime* runtime);
static void bb_0C_8179(SCV11Runtime* runtime);
static void bb_0C_817A(SCV11Runtime* runtime);
static void bb_0C_8180(SCV11Runtime* runtime);
static void bb_0C_8182(SCV11Runtime* runtime);
static void bb_0C_8184(SCV11Runtime* runtime);
static void bb_0C_8186(SCV11Runtime* runtime);
static void bb_0C_818B(SCV11Runtime* runtime);
static void bb_0C_818D(SCV11Runtime* runtime);
static void bb_0C_818F(SCV11Runtime* runtime);
static void bb_0C_8192(SCV11Runtime* runtime);
static void bb_0C_8194(SCV11Runtime* runtime);
static void bb_0C_8195(SCV11Runtime* runtime);
static void bb_0C_8196(SCV11Runtime* runtime);
static void bb_0C_8197(SCV11Runtime* runtime);
static void bb_0C_8198(SCV11Runtime* runtime);
static void bb_0C_81A2(SCV11Runtime* runtime);
static void bb_0C_81A4(SCV11Runtime* runtime);
static void bb_0C_81A5(SCV11Runtime* runtime);
static void bb_0C_81A7(SCV11Runtime* runtime);
static void bb_0C_81A8(SCV11Runtime* runtime);
static void bb_0C_81AA(SCV11Runtime* runtime);
static void bb_0C_81AD(SCV11Runtime* runtime);
static void bb_0C_81AF(SCV11Runtime* runtime);
static void bb_0C_81B2(SCV11Runtime* runtime);
static void bb_0C_81B5(SCV11Runtime* runtime);
static void bb_0C_81B6(SCV11Runtime* runtime);
static void bb_0C_81BF(SCV11Runtime* runtime);
static void bb_0C_81C1(SCV11Runtime* runtime);
static void bb_0C_81C2(SCV11Runtime* runtime);
static void bb_0C_81C3(SCV11Runtime* runtime);


/* Block bb_00_2020 at bank=00 addr=2020 */
static void bb_00_2020(SCV11Runtime* runtime) {
    /* ASL dp 0680068006 */
    /* TODO: ASL dp */
    runtime->route_failed = 1; return;
    bb_00_2025(runtime);
}


/* Block bb_00_2025 at bank=00 addr=2025 */
static void bb_00_2025(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $202D */
    runtime->machine.cpu.pc = 0x202Du;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_202D(runtime);
    return;
}


/* Block bb_00_202D at bank=00 addr=202D */
static void bb_00_202D(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $2035 */
    runtime->machine.cpu.pc = 0x2035u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2035(runtime);
    return;
}


/* Block bb_00_2035 at bank=00 addr=2035 */
static void bb_00_2035(SCV11Runtime* runtime) {
    /* BRA 8003 */
    /* BRA $03 -> $203A */
    runtime->machine.cpu.pc = 0x203Au;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_203A(runtime);
    return;
}


/* Block bb_00_203A at bank=00 addr=203A */
static void bb_00_203A(SCV11Runtime* runtime) {
    /* ASL dp 0680068009 */
    /* TODO: ASL dp */
    runtime->route_failed = 1; return;
    bb_00_203F(runtime);
}


/* Block bb_00_203F at bank=00 addr=203F */
static void bb_00_203F(SCV11Runtime* runtime) {
    /* BRA 8009 */
    /* BRA $09 -> $204A */
    runtime->machine.cpu.pc = 0x204Au;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_204A(runtime);
    return;
}


/* Block bb_00_204A at bank=00 addr=204A */
static void bb_00_204A(SCV11Runtime* runtime) {
    /* ASL dp 0680068006 */
    /* TODO: ASL dp */
    runtime->route_failed = 1; return;
    bb_00_204F(runtime);
}


/* Block bb_00_204F at bank=00 addr=204F */
static void bb_00_204F(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $2057 */
    runtime->machine.cpu.pc = 0x2057u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2057(runtime);
    return;
}


/* Block bb_00_2057 at bank=00 addr=2057 */
static void bb_00_2057(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $205F */
    runtime->machine.cpu.pc = 0x205Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_205F(runtime);
    return;
}


/* Block bb_00_205F at bank=00 addr=205F */
static void bb_00_205F(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2061 */
    runtime->machine.cpu.pc = 0x2061u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2061(runtime);
    return;
}


/* Block bb_00_2061 at bank=00 addr=2061 */
static void bb_00_2061(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2063 */
    runtime->machine.cpu.pc = 0x2063u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2063(runtime);
    return;
}


/* Block bb_00_2063 at bank=00 addr=2063 */
static void bb_00_2063(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2065 */
    runtime->machine.cpu.pc = 0x2065u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2065(runtime);
    return;
}


/* Block bb_00_2065 at bank=00 addr=2065 */
static void bb_00_2065(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2067 */
    runtime->machine.cpu.pc = 0x2067u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2067(runtime);
    return;
}


/* Block bb_00_2067 at bank=00 addr=2067 */
static void bb_00_2067(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2069 */
    runtime->machine.cpu.pc = 0x2069u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2069(runtime);
    return;
}


/* Block bb_00_2069 at bank=00 addr=2069 */
static void bb_00_2069(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $206B */
    runtime->machine.cpu.pc = 0x206Bu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_206B(runtime);
    return;
}


/* Block bb_00_206B at bank=00 addr=206B */
static void bb_00_206B(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $206D */
    runtime->machine.cpu.pc = 0x206Du;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_206D(runtime);
    return;
}


/* Block bb_00_206D at bank=00 addr=206D */
static void bb_00_206D(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $206F */
    runtime->machine.cpu.pc = 0x206Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_206F(runtime);
    return;
}


/* Block bb_00_206F at bank=00 addr=206F */
static void bb_00_206F(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2071 */
    runtime->machine.cpu.pc = 0x2071u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2071(runtime);
    return;
}


/* Block bb_00_2071 at bank=00 addr=2071 */
static void bb_00_2071(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2073 */
    runtime->machine.cpu.pc = 0x2073u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2073(runtime);
    return;
}


/* Block bb_00_2073 at bank=00 addr=2073 */
static void bb_00_2073(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2075 */
    runtime->machine.cpu.pc = 0x2075u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2075(runtime);
    return;
}


/* Block bb_00_2075 at bank=00 addr=2075 */
static void bb_00_2075(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2077 */
    runtime->machine.cpu.pc = 0x2077u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2077(runtime);
    return;
}


/* Block bb_00_2077 at bank=00 addr=2077 */
static void bb_00_2077(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2079 */
    runtime->machine.cpu.pc = 0x2079u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2079(runtime);
    return;
}


/* Block bb_00_2079 at bank=00 addr=2079 */
static void bb_00_2079(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $207B */
    runtime->machine.cpu.pc = 0x207Bu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_207B(runtime);
    return;
}


/* Block bb_00_207B at bank=00 addr=207B */
static void bb_00_207B(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $207D */
    runtime->machine.cpu.pc = 0x207Du;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_207D(runtime);
    return;
}


/* Block bb_00_207D at bank=00 addr=207D */
static void bb_00_207D(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $207F */
    runtime->machine.cpu.pc = 0x207Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_207F(runtime);
    return;
}


/* Block bb_00_207F at bank=00 addr=207F */
static void bb_00_207F(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $2087 */
    runtime->machine.cpu.pc = 0x2087u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2087(runtime);
    return;
}


/* Block bb_00_2087 at bank=00 addr=2087 */
static void bb_00_2087(SCV11Runtime* runtime) {
    /* BRA 8006 */
    /* BRA $06 -> $208F */
    runtime->machine.cpu.pc = 0x208Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_208F(runtime);
    return;
}


/* Block bb_00_208F at bank=00 addr=208F */
static void bb_00_208F(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2091 */
    runtime->machine.cpu.pc = 0x2091u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2091(runtime);
    return;
}


/* Block bb_00_2091 at bank=00 addr=2091 */
static void bb_00_2091(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2093 */
    runtime->machine.cpu.pc = 0x2093u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2093(runtime);
    return;
}


/* Block bb_00_2093 at bank=00 addr=2093 */
static void bb_00_2093(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2095 */
    runtime->machine.cpu.pc = 0x2095u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2095(runtime);
    return;
}


/* Block bb_00_2095 at bank=00 addr=2095 */
static void bb_00_2095(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2097 */
    runtime->machine.cpu.pc = 0x2097u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2097(runtime);
    return;
}


/* Block bb_00_2097 at bank=00 addr=2097 */
static void bb_00_2097(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $2099 */
    runtime->machine.cpu.pc = 0x2099u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_2099(runtime);
    return;
}


/* Block bb_00_2099 at bank=00 addr=2099 */
static void bb_00_2099(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $209B */
    runtime->machine.cpu.pc = 0x209Bu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_209B(runtime);
    return;
}


/* Block bb_00_209B at bank=00 addr=209B */
static void bb_00_209B(SCV11Runtime* runtime) {
    /* BRA 8000 */
    /* BRA $00 -> $209D */
    runtime->machine.cpu.pc = 0x209Du;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_209D(runtime);
    return;
}


/* Block bb_00_209D at bank=00 addr=209D */
static void bb_00_209D(SCV11Runtime* runtime) {
    /* BRA 80c0 */
    /* BRA $FFC0 -> $205F */
    runtime->machine.cpu.pc = 0x205Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_205F(runtime);
    return;
}


/* Block bb_00_7FC2 at bank=00 addr=7FC2 */
static void bb_00_7FC2(SCV11Runtime* runtime) {
    /* LSR 4f50 */
    /* LSR memory - stub */
    runtime->route_failed = 1; return;
    bb_00_7FC4(runtime);
}


/* Block bb_00_7FC4 at bank=00 addr=7FC4 */
static void bb_00_7FC4(SCV11Runtime* runtime) {
    /* EOR #imm 4941 */
    /* TODO: EOR #imm */
    runtime->route_failed = 1; return;
    bb_00_7FC6(runtime);
}


/* Block bb_00_7FC6 at bank=00 addr=7FC6 */
static void bb_00_7FC6(SCV11Runtime* runtime) {
    /* JSR 202020 */
    /* JSR */
    /* JSR $2020 */
    stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
    stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
    runtime->machine.cpu.pc = 0x2020u;
    runtime->scheduler.cpu_instructions += 6;
    runtime->scheduler.master_clock += 6;
    return;
    bb_00_2020(runtime);
    return;
}


/* Block bb_00_800C at bank=00 addr=800C */
static void bb_00_800C(SCV11Runtime* runtime) {
    /* REP #imm c23048 */
    /* TODO: REP #imm */
    runtime->route_failed = 1; return;
    bb_00_800F(runtime);
}


/* Block bb_00_800F at bank=00 addr=800F */
static void bb_00_800F(SCV11Runtime* runtime) {
    /* PHX da */
    /* PHX */
    stack_push(runtime, runtime->machine.cpu.x);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8010(runtime);
}


/* Block bb_00_8010 at bank=00 addr=8010 */
static void bb_00_8010(SCV11Runtime* runtime) {
    /* PHY 5a */
    /* PHY */
    stack_push(runtime, (uint8_t)runtime->machine.cpu.y);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8011(runtime);
}


/* Block bb_00_8011 at bank=00 addr=8011 */
static void bb_00_8011(SCV11Runtime* runtime) {
    /* PHD 0b */
    /* PHD */
    stack_push(runtime, (uint8_t)(runtime->machine.cpu.d >> 8));
    stack_push(runtime, (uint8_t)runtime->machine.cpu.d);
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_00_8012(runtime);
}


/* Block bb_00_8012 at bank=00 addr=8012 */
static void bb_00_8012(SCV11Runtime* runtime) {
    /* PHK 8b */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8013(runtime);
}


/* Block bb_00_8013 at bank=00 addr=8013 */
static void bb_00_8013(SCV11Runtime* runtime) {
    /* LDA #imm a900 */
    /* TODO: LDA #imm */
    runtime->route_failed = 1; return;
    bb_00_8015(runtime);
}


/* Block bb_00_8015 at bank=00 addr=8015 */
static void bb_00_8015(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_8016(runtime);
}


/* Block bb_00_8016 at bank=00 addr=8016 */
static void bb_00_8016(SCV11Runtime* runtime) {
    /* TCD 5b */
    /* TCD - Transfer A to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.a;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_8017(runtime);
}


/* Block bb_00_8017 at bank=00 addr=8017 */
static void bb_00_8017(SCV11Runtime* runtime) {
    /* PHK 4b */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8018(runtime);
}


/* Block bb_00_8018 at bank=00 addr=8018 */
static void bb_00_8018(SCV11Runtime* runtime) {
    /* PHK ab */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8019(runtime);
}


/* Block bb_00_8019 at bank=00 addr=8019 */
static void bb_00_8019(SCV11Runtime* runtime) {
    /* LDA abs ad1042 */
    /* TODO: LDA abs */
    runtime->route_failed = 1; return;
    bb_00_801C(runtime);
}


/* Block bb_00_801C at bank=00 addr=801C */
static void bb_00_801C(SCV11Runtime* runtime) {
    /* LDA dp a5e2d0 */
    /* TODO: LDA dp */
    runtime->route_failed = 1; return;
    bb_00_801F(runtime);
}


/* Block bb_00_801F at bank=00 addr=801F */
static void bb_00_801F(SCV11Runtime* runtime) {
    /* PHP 08 */
    /* PHP */
    stack_push(runtime, runtime->machine.cpu.status | 0x30);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_8020(runtime);
}


/* Block bb_00_8020 at bank=00 addr=8020 */
static void bb_00_8020(SCV11Runtime* runtime) {
    /* LDA #imm a900 */
    /* TODO: LDA #imm */
    runtime->route_failed = 1; return;
    bb_00_8022(runtime);
}


/* Block bb_00_8022 at bank=00 addr=8022 */
static void bb_00_8022(SCV11Runtime* runtime) {
    /* CPY #imm c00c */
    /* TODO: CPY #imm */
    runtime->route_failed = 1; return;
    bb_00_8024(runtime);
}


/* Block bb_00_8024 at bank=00 addr=8024 */
static void bb_00_8024(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_8025(runtime);
}


/* Block bb_00_8025 at bank=00 addr=8025 */
static void bb_00_8025(SCV11Runtime* runtime) {
    /* TSD 04 */
    /* TSD - Transfer Stack Pointer to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.sp;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_8026(runtime);
}


/* Block bb_00_8026 at bank=00 addr=8026 */
static void bb_00_8026(SCV11Runtime* runtime) {
    /* BRA 8009 */
    /* BRA $09 -> $8031 */
    runtime->machine.cpu.pc = 0x8031u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_8031(runtime);
    return;
}


/* Block bb_00_8031 at bank=00 addr=8031 */
static void bb_00_8031(SCV11Runtime* runtime) {
    /* LDA #imm a90e */
    /* TODO: LDA #imm */
    runtime->route_failed = 1; return;
    bb_00_8033(runtime);
}


/* Block bb_00_8033 at bank=00 addr=8033 */
static void bb_00_8033(SCV11Runtime* runtime) {
    /* BRA 808d */
    /* BRA $FF8D -> $7FC2 */
    runtime->machine.cpu.pc = 0x7FC2u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_00_7FC2(runtime);
    return;
}


/* Block bb_00_81A2 at bank=00 addr=81A2 */
static void bb_00_81A2(SCV11Runtime* runtime) {
    /* RTI 40 */
    /* RTI */
    {
        uint8_t status = stack_pop(runtime);
        uint16_t pc_lo = stack_pop(runtime);
        uint16_t pc_hi = stack_pop(runtime);
        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo);
        runtime->machine.cpu.status = (status & ~0x30) | 0x20; /* clear B, set U */
        runtime->scheduler.cpu_instructions += 6;
        runtime->scheduler.master_clock += 6;
        return;
    }
    return;
}


/* Block bb_00_81A7 at bank=00 addr=81A7 */
static void bb_00_81A7(SCV11Runtime* runtime) {
    /* REP #imm c23048 */
    /* TODO: REP #imm */
    runtime->route_failed = 1; return;
    bb_00_81AA(runtime);
}


/* Block bb_00_81AA at bank=00 addr=81AA */
static void bb_00_81AA(SCV11Runtime* runtime) {
    /* PHX da */
    /* PHX */
    stack_push(runtime, runtime->machine.cpu.x);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_81AB(runtime);
}


/* Block bb_00_81AB at bank=00 addr=81AB */
static void bb_00_81AB(SCV11Runtime* runtime) {
    /* PHY 5a */
    /* PHY */
    stack_push(runtime, (uint8_t)runtime->machine.cpu.y);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_81AC(runtime);
}


/* Block bb_00_81AC at bank=00 addr=81AC */
static void bb_00_81AC(SCV11Runtime* runtime) {
    /* PHD 0b */
    /* PHD */
    stack_push(runtime, (uint8_t)(runtime->machine.cpu.d >> 8));
    stack_push(runtime, (uint8_t)runtime->machine.cpu.d);
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_00_81AD(runtime);
}


/* Block bb_00_81AD at bank=00 addr=81AD */
static void bb_00_81AD(SCV11Runtime* runtime) {
    /* PHK 8b */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_81AE(runtime);
}


/* Block bb_00_81AE at bank=00 addr=81AE */
static void bb_00_81AE(SCV11Runtime* runtime) {
    /* LDA #imm a900 */
    /* TODO: LDA #imm */
    runtime->route_failed = 1; return;
    bb_00_81B0(runtime);
}


/* Block bb_00_81B0 at bank=00 addr=81B0 */
static void bb_00_81B0(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_81B1(runtime);
}


/* Block bb_00_81B1 at bank=00 addr=81B1 */
static void bb_00_81B1(SCV11Runtime* runtime) {
    /* TCD 5b */
    /* TCD - Transfer A to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.a;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_81B2(runtime);
}


/* Block bb_00_81B2 at bank=00 addr=81B2 */
static void bb_00_81B2(SCV11Runtime* runtime) {
    /* PHK 4b */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_81B3(runtime);
}


/* Block bb_00_81B3 at bank=00 addr=81B3 */
static void bb_00_81B3(SCV11Runtime* runtime) {
    /* PHK ab */
    /* PHK */
    stack_push(runtime, runtime->machine.cpu.bank);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_00_81B4(runtime);
}


/* Block bb_00_81B4 at bank=00 addr=81B4 */
static void bb_00_81B4(SCV11Runtime* runtime) {
    /* SEP #imm e220ad */
    /* TODO: SEP #imm */
    runtime->route_failed = 1; return;
    bb_00_81B7(runtime);
}


/* Block bb_00_81B7 at bank=00 addr=81B7 */
static void bb_00_81B7(SCV11Runtime* runtime) {
    /* ORA (ind,S),Y 1142ad2c00 */
    /* TODO: ORA (ind,S),Y */
    runtime->route_failed = 1; return;
    bb_00_81BC(runtime);
}


/* Block bb_00_81BC at bank=00 addr=81BC */
static void bb_00_81BC(SCV11Runtime* runtime) {
    /* ASL A 0a */
    /* TODO: ASL A */
    runtime->route_failed = 1; return;
    bb_00_81BD(runtime);
}


/* Block bb_00_81BD at bank=00 addr=81BD */
static void bb_00_81BD(SCV11Runtime* runtime) {
    /* TAX aa */
    /* TAX */
    runtime->machine.cpu.x = runtime->machine.cpu.a;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_81BE(runtime);
}


/* Block bb_00_81BE at bank=00 addr=81BE */
static void bb_00_81BE(SCV11Runtime* runtime) {
    /* CPX #imm e00d */
    /* TODO: CPX #imm */
    runtime->route_failed = 1; return;
    bb_00_81C0(runtime);
}


/* Block bb_00_81C0 at bank=00 addr=81C0 */
static void bb_00_81C0(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_81C1(runtime);
}


/* Block bb_00_81C1 at bank=00 addr=81C1 */
static void bb_00_81C1(SCV11Runtime* runtime) {
    /* BCC 9003 */
    /* TODO: BCC */
    runtime->route_failed = 1; return;
    bb_00_81C6(runtime);
    return;
}


/* Block bb_00_81C6 at bank=00 addr=81C6 */
static void bb_00_81C6(SCV11Runtime* runtime) {
    /* MVD 7c */
    /* MVD - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_00_81C7(runtime);
}


/* Block bb_00_81C7 at bank=00 addr=81C7 */
static void bb_00_81C7(SCV11Runtime* runtime) {
    /* CMP #imm c981 */
    /* TODO: CMP #imm */
    runtime->route_failed = 1; return;
    bb_00_81C9(runtime);
}


/* Block bb_00_81C9 at bank=00 addr=81C9 */
static void bb_00_81C9(SCV11Runtime* runtime) {
    /* PLP 28 */
    /* PLP */
    {
        uint8_t status = stack_pop(runtime);
        runtime->machine.cpu.status = (status & ~0x30) | 0x20;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    }
    bb_00_81CA(runtime);
}


/* Block bb_00_81CA at bank=00 addr=81CA */
static void bb_00_81CA(SCV11Runtime* runtime) {
    /* STA (ind,S) 82d7810f8230 */
    /* TODO: STA (ind,S) */
    runtime->route_failed = 1; return;
    bb_00_81D0(runtime);
}


/* Block bb_00_81D0 at bank=00 addr=81D0 */
static void bb_00_81D0(SCV11Runtime* runtime) {
    /* STA (ind,S) 8241826a8298 */
    /* TODO: STA (ind,S) */
    runtime->route_failed = 1; return;
    bb_00_81D6(runtime);
}


/* Block bb_00_81D6 at bank=00 addr=81D6 */
static void bb_00_81D6(SCV11Runtime* runtime) {
    /* STA (ind,S) 82a5320a652e */
    /* TODO: STA (ind,S) */
    runtime->route_failed = 1; return;
    bb_00_81DC(runtime);
}


/* Block bb_00_81DC at bank=00 addr=81DC */
static void bb_00_81DC(SCV11Runtime* runtime) {
    /* STA abs 8d0942 */
    /* TODO: STA abs */
    runtime->route_failed = 1; return;
    bb_00_81DF(runtime);
}


/* Block bb_00_81DF at bank=00 addr=81DF */
static void bb_00_81DF(SCV11Runtime* runtime) {
    /* LDA dp a5340a */
    /* TODO: LDA dp */
    runtime->route_failed = 1; return;
    bb_00_81E2(runtime);
}


/* Block bb_00_81E2 at bank=00 addr=81E2 */
static void bb_00_81E2(SCV11Runtime* runtime) {
    /* SEC 38 */
    /* SEC */
    runtime->machine.cpu.status |= 0x01;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_81E3(runtime);
}


/* Block bb_00_81E3 at bank=00 addr=81E3 */
static void bb_00_81E3(SCV11Runtime* runtime) {
    /* SBC dp e52e3a */
    /* TODO: SBC dp */
    runtime->route_failed = 1; return;
    bb_00_81E6(runtime);
}


/* Block bb_00_81E6 at bank=00 addr=81E6 */
static void bb_00_81E6(SCV11Runtime* runtime) {
    /* STA abs 8d1221 */
    /* TODO: STA abs */
    runtime->route_failed = 1; return;
    bb_00_81E9(runtime);
}


/* Block bb_00_81E9 at bank=00 addr=81E9 */
static void bb_00_81E9(SCV11Runtime* runtime) {
    /* STZ dp 9c1221 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_00_81EC(runtime);
}


/* Block bb_00_81EC at bank=00 addr=81EC */
static void bb_00_81EC(SCV11Runtime* runtime) {
    /* LDX #imm a208 */
    /* TODO: LDX #imm */
    runtime->route_failed = 1; return;
    bb_00_81EE(runtime);
}


/* Block bb_00_81EE at bank=00 addr=81EE */
static void bb_00_81EE(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_81EF(runtime);
}


/* Block bb_00_81EF at bank=00 addr=81EF */
static void bb_00_81EF(SCV11Runtime* runtime) {
    /* DEX ca */
    /* DEX */
    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_81F0(runtime);
}


/* Block bb_00_81F0 at bank=00 addr=81F0 */
static void bb_00_81F0(SCV11Runtime* runtime) {
    /* BPL 10fd */
    /* BPL -> $81EF if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81EFu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_00_81EF(runtime);
    return;
}


/* Block bb_00_82B7 at bank=00 addr=82B7 */
static void bb_00_82B7(SCV11Runtime* runtime) {
    /* CLD d8 */
    /* CLD */
    runtime->machine.cpu.status &= ~0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_82B8(runtime);
}


/* Block bb_00_82B8 at bank=00 addr=82B8 */
static void bb_00_82B8(SCV11Runtime* runtime) {
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_82B9(runtime);
}


/* Block bb_00_82B9 at bank=00 addr=82B9 */
static void bb_00_82B9(SCV11Runtime* runtime) {
    /* SEP #imm e22018 */
    /* TODO: SEP #imm */
    runtime->route_failed = 1; return;
    bb_00_82BC(runtime);
}


/* Block bb_00_82BC at bank=00 addr=82BC */
static void bb_00_82BC(SCV11Runtime* runtime) {
    /* XCE fb */
    /* TODO: XCE */
    runtime->route_failed = 1; return;
    bb_00_82BD(runtime);
}


/* Block bb_00_82BD at bank=00 addr=82BD */
static void bb_00_82BD(SCV11Runtime* runtime) {
    /* STZ dp 9c0042 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_00_82C0(runtime);
}


/* Block bb_00_82C0 at bank=00 addr=82C0 */
static void bb_00_82C0(SCV11Runtime* runtime) {
    /* REP #imm c2309c */
    /* TODO: REP #imm */
    runtime->route_failed = 1; return;
    bb_00_82C3(runtime);
}


/* Block bb_00_82C3 at bank=00 addr=82C3 */
static void bb_00_82C3(SCV11Runtime* runtime) {
    /* PHD 0b */
    /* PHD */
    stack_push(runtime, (uint8_t)(runtime->machine.cpu.d >> 8));
    stack_push(runtime, (uint8_t)runtime->machine.cpu.d);
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_00_82C4(runtime);
}


/* Block bb_00_82C4 at bank=00 addr=82C4 */
static void bb_00_82C4(SCV11Runtime* runtime) {
    /* WDM 42a9 */
    /* WDM - Reserved */
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_82C6(runtime);
}


/* Block bb_00_82C6 at bank=00 addr=82C6 */
static void bb_00_82C6(SCV11Runtime* runtime) {
    /* INC abs fe011b */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    bb_00_82C9(runtime);
}


/* Block bb_00_82C9 at bank=00 addr=82C9 */
static void bb_00_82C9(SCV11Runtime* runtime) {
    /* LDA #imm a900 */
    /* TODO: LDA #imm */
    runtime->route_failed = 1; return;
    bb_00_82CB(runtime);
}


/* Block bb_00_82CB at bank=00 addr=82CB */
static void bb_00_82CB(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_82CC(runtime);
}


/* Block bb_00_82CC at bank=00 addr=82CC */
static void bb_00_82CC(SCV11Runtime* runtime) {
    /* TCD 5b */
    /* TCD - Transfer A to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.a;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_82CD(runtime);
}


/* Block bb_00_82CD at bank=00 addr=82CD */
static void bb_00_82CD(SCV11Runtime* runtime) {
    /* LDX #imm a2fe */
    /* TODO: LDX #imm */
    runtime->route_failed = 1; return;
    bb_00_82CF(runtime);
}


/* Block bb_00_82CF at bank=00 addr=82CF */
static void bb_00_82CF(SCV11Runtime* runtime) {
    /* ASL 1f9e */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* DEX ca */
    /* DEX */
    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* BPL 10fa */
    /* BPL -> $82D0 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x82D0u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_00_82D0(runtime);
    return;
}


/* Block bb_00_82D0 at bank=00 addr=82D0 */
static void bb_00_82D0(SCV11Runtime* runtime) {
    /* STZ dp 9e0000 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    /* DEX ca */
    /* DEX */
    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* BPL 10fa */
    /* BPL -> $82D0 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x82D0u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_00_82D0(runtime);
    return;
}


/* Block bb_00_82D1 at bank=00 addr=82D1 */
static void bb_00_82D1(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_82D2(runtime);
}


/* Block bb_00_82D2 at bank=00 addr=82D2 */
static void bb_00_82D2(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_00_82D3(runtime);
}


/* Block bb_00_82D3 at bank=00 addr=82D3 */
static void bb_00_82D3(SCV11Runtime* runtime) {
    /* DEX ca */
    /* DEX */
    runtime->machine.cpu.x = (runtime->machine.cpu.x - 1) & 0xFFFF;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_00_82D4(runtime);
}


/* Block bb_00_82D4 at bank=00 addr=82D4 */
static void bb_00_82D4(SCV11Runtime* runtime) {
    /* BPL 10fa */
    /* BPL -> $82D0 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x82D0u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_00_82D0(runtime);
    return;
}


/* Block bb_01_8141 at bank=01 addr=8141 */
static void bb_01_8141(SCV11Runtime* runtime) {
    /* TSD 04 */
    /* TSD - Transfer Stack Pointer to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.sp;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_8142(runtime);
}


/* Block bb_01_8142 at bank=01 addr=8142 */
static void bb_01_8142(SCV11Runtime* runtime) {
    /* EOR abs ef356b */
    /* TODO: EOR abs */
    runtime->route_failed = 1; return;
    bb_01_8145(runtime);
}


/* Block bb_01_8145 at bank=01 addr=8145 */
static void bb_01_8145(SCV11Runtime* runtime) {
    /* AND dp 25e714 */
    /* TODO: AND dp */
    runtime->route_failed = 1; return;
    bb_01_8148(runtime);
}


/* Block bb_01_8148 at bank=01 addr=8148 */
static void bb_01_8148(SCV11Runtime* runtime) {
    /* AND (ind,X) 2106a105737e */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_814E(runtime);
}


/* Block bb_01_814E at bank=01 addr=814E */
static void bb_01_814E(SCV11Runtime* runtime) {
    /* LDA abs ad6de7 */
    /* TODO: LDA abs */
    runtime->route_failed = 1; return;
    bb_01_8151(runtime);
}


/* Block bb_01_8151 at bank=01 addr=8151 */
static void bb_01_8151(SCV11Runtime* runtime) {
    /* NEG dp 54f706 */
    /* TODO: NEG dp */
    runtime->route_failed = 1; return;
    bb_01_8154(runtime);
}


/* Block bb_01_8154 at bank=01 addr=8154 */
static void bb_01_8154(SCV11Runtime* runtime) {
    /* SBC (ind,S),Y f304af042f */
    /* TODO: SBC (ind,S),Y */
    runtime->route_failed = 1; return;
    bb_01_8159(runtime);
}


/* Block bb_01_8159 at bank=01 addr=8159 */
static void bb_01_8159(SCV11Runtime* runtime) {
    /* TSD 04 */
    /* TSD - Transfer Stack Pointer to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.sp;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_815A(runtime);
}


/* Block bb_01_815A at bank=01 addr=815A */
static void bb_01_815A(SCV11Runtime* runtime) {
    /* LDX dp b70535 */
    /* TODO: LDX dp */
    runtime->route_failed = 1; return;
    bb_01_815D(runtime);
}


/* Block bb_01_815D at bank=01 addr=815D */
static void bb_01_815D(SCV11Runtime* runtime) {
    /* ORA dp 052104 */
    /* TODO: ORA dp */
    runtime->route_failed = 1; return;
    bb_01_8160(runtime);
}


/* Block bb_01_8160 at bank=01 addr=8160 */
static void bb_01_8160(SCV11Runtime* runtime) {
    /* AND (ind,X) 21043146ad35 */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_8166(runtime);
}


/* Block bb_01_8166 at bank=01 addr=8166 */
static void bb_01_8166(SCV11Runtime* runtime) {
    /* AND #imm 2925 */
    /* TODO: AND #imm */
    runtime->route_failed = 1; return;
    bb_01_8168(runtime);
}


/* Block bb_01_8168 at bank=01 addr=8168 */
static void bb_01_8168(SCV11Runtime* runtime) {
    /* ADC (ind,X) 6106a105b56e */
    /* TODO: ADC (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_816E(runtime);
}


/* Block bb_01_816E at bank=01 addr=816E */
static void bb_01_816E(SCV11Runtime* runtime) {
    /* AND (ind,S),Y 315ead55ff */
    /* TODO: AND (ind,S),Y */
    runtime->route_failed = 1; return;
    bb_01_8173(runtime);
}


/* Block bb_01_8173 at bank=01 addr=8173 */
static void bb_01_8173(SCV11Runtime* runtime) {
    /* PHP 07 */
    /* PHP */
    stack_push(runtime, runtime->machine.cpu.status | 0x30);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_01_8174(runtime);
}


/* Block bb_01_8174 at bank=01 addr=8174 */
static void bb_01_8174(SCV11Runtime* runtime) {
    /* ASL dp 370433042f */
    /* TODO: ASL dp */
    runtime->route_failed = 1; return;
    bb_01_8179(runtime);
}


/* Block bb_01_8179 at bank=01 addr=8179 */
static void bb_01_8179(SCV11Runtime* runtime) {
    /* TSD 04 */
    /* TSD - Transfer Stack Pointer to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.sp;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_817A(runtime);
}


/* Block bb_01_817A at bank=01 addr=817A */
static void bb_01_817A(SCV11Runtime* runtime) {
    /* LDX dp b70535 */
    /* TODO: LDX dp */
    runtime->route_failed = 1; return;
    bb_01_817D(runtime);
}


/* Block bb_01_817D at bank=01 addr=817D */
static void bb_01_817D(SCV11Runtime* runtime) {
    /* ORA dp 052104 */
    /* TODO: ORA dp */
    runtime->route_failed = 1; return;
    bb_01_8180(runtime);
}


/* Block bb_01_8180 at bank=01 addr=8180 */
static void bb_01_8180(SCV11Runtime* runtime) {
    /* STA dp 921910 */
    /* TODO: STA dp */
    runtime->route_failed = 1; return;
    bb_01_8183(runtime);
}


/* Block bb_01_8183 at bank=01 addr=8183 */
static void bb_01_8183(SCV11Runtime* runtime) {
    /* WDM 428c */
    /* WDM - Reserved */
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_8185(runtime);
}


/* Block bb_01_8185 at bank=01 addr=8185 */
static void bb_01_8185(SCV11Runtime* runtime) {
    /* AND (ind,S),Y 3108214002 */
    /* TODO: AND (ind,S),Y */
    runtime->route_failed = 1; return;
    bb_01_818A(runtime);
}


/* Block bb_01_818A at bank=01 addr=818A */
static void bb_01_818A(SCV11Runtime* runtime) {
    /* BRA 8001 */
    /* BRA $01 -> $818D */
    runtime->machine.cpu.pc = 0x818Du;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_01_818D(runtime);
    return;
}


/* Block bb_01_818D at bank=01 addr=818D */
static void bb_01_818D(SCV11Runtime* runtime) {
    /* ROR A 6a */
    /* TODO: ROR A */
    runtime->route_failed = 1; return;
    bb_01_818E(runtime);
}


/* Block bb_01_818E at bank=01 addr=818E */
static void bb_01_818E(SCV11Runtime* runtime) {
    /* BPL 105a */
    /* BPL -> $81EA if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81EAu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_81EA(runtime);
    return;
}


/* Block bb_01_81A7 at bank=01 addr=81A7 */
static void bb_01_81A7(SCV11Runtime* runtime) {
    /* COP 0280 */
    /* TODO: COP */
    runtime->route_failed = 1; return;
    bb_01_81A9(runtime);
}


/* Block bb_01_81A9 at bank=01 addr=81A9 */
static void bb_01_81A9(SCV11Runtime* runtime) {
    /* ROR A 6a */
    /* TODO: ROR A */
    runtime->route_failed = 1; return;
    bb_01_81AA(runtime);
}


/* Block bb_01_81AA at bank=01 addr=81AA */
static void bb_01_81AA(SCV11Runtime* runtime) {
    /* BRA 8001 */
    /* BRA $01 -> $81AD */
    runtime->machine.cpu.pc = 0x81ADu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_01_81AD(runtime);
    return;
}


/* Block bb_01_81AD at bank=01 addr=81AD */
static void bb_01_81AD(SCV11Runtime* runtime) {
    /* AND (ind,S) 039e011e */
    /* TODO: AND (ind,S) */
    runtime->route_failed = 1; return;
    bb_01_81B1(runtime);
}


/* Block bb_01_81B1 at bank=01 addr=81B1 */
static void bb_01_81B1(SCV11Runtime* runtime) {
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_81B2(runtime);
}


/* Block bb_01_81B2 at bank=01 addr=81B2 */
static void bb_01_81B2(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_81B3(runtime);
}


/* Block bb_01_81B3 at bank=01 addr=81B3 */
static void bb_01_81B3(SCV11Runtime* runtime) {
    /* BVC 508c */
    /* BVC -> $8141 if V=0 */
    if ((runtime->machine.cpu.status & 0x40) == 0) {
        runtime->machine.cpu.pc = 0x8141u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_8141(runtime);
    return;
}


/* Block bb_01_81EA at bank=01 addr=81EA */
static void bb_01_81EA(SCV11Runtime* runtime) {
    /* AND (ind,X) 210421042104 */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_81F0(runtime);
}


/* Block bb_01_81F0 at bank=01 addr=81F0 */
static void bb_01_81F0(SCV11Runtime* runtime) {
    /* AND (ind,X) 210421042104 */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_81F6(runtime);
}


/* Block bb_01_81F6 at bank=01 addr=81F6 */
static void bb_01_81F6(SCV11Runtime* runtime) {
    /* AND (ind,X) 210421042104 */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_81FC(runtime);
}


/* Block bb_01_81FC at bank=01 addr=81FC */
static void bb_01_81FC(SCV11Runtime* runtime) {
    /* AND (ind,X) 210421043104 */
    /* TODO: AND (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_8202(runtime);
}


/* Block bb_01_8202 at bank=01 addr=8202 */
static void bb_01_8202(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8203(runtime);
}


/* Block bb_01_8203 at bank=01 addr=8203 */
static void bb_01_8203(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8204(runtime);
}


/* Block bb_01_8204 at bank=01 addr=8204 */
static void bb_01_8204(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8205(runtime);
}


/* Block bb_01_8205 at bank=01 addr=8205 */
static void bb_01_8205(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8206(runtime);
}


/* Block bb_01_8206 at bank=01 addr=8206 */
static void bb_01_8206(SCV11Runtime* runtime) {
    /* BRA 8001 */
    /* BRA $01 -> $8209 */
    runtime->machine.cpu.pc = 0x8209u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_01_8209(runtime);
    return;
}


/* Block bb_01_8209 at bank=01 addr=8209 */
static void bb_01_8209(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_820A(runtime);
}


/* Block bb_01_820A at bank=01 addr=820A */
static void bb_01_820A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_820B(runtime);
}


/* Block bb_01_820B at bank=01 addr=820B */
static void bb_01_820B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_820C(runtime);
}


/* Block bb_01_820C at bank=01 addr=820C */
static void bb_01_820C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_820D(runtime);
}


/* Block bb_01_820D at bank=01 addr=820D */
static void bb_01_820D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_820E(runtime);
}


/* Block bb_01_820E at bank=01 addr=820E */
static void bb_01_820E(SCV11Runtime* runtime) {
    /* STZ dp 9e021e */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_01_8211(runtime);
}


/* Block bb_01_8211 at bank=01 addr=8211 */
static void bb_01_8211(SCV11Runtime* runtime) {
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_01_8212(runtime);
}


/* Block bb_01_8212 at bank=01 addr=8212 */
static void bb_01_8212(SCV11Runtime* runtime) {
    /* STZ dp 9e01c0 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_01_8215(runtime);
}


/* Block bb_01_8215 at bank=01 addr=8215 */
static void bb_01_8215(SCV11Runtime* runtime) {
    /* AND (ind,S) 03000000 */
    /* TODO: AND (ind,S) */
    runtime->route_failed = 1; return;
    bb_01_8219(runtime);
}


/* Block bb_01_8219 at bank=01 addr=8219 */
static void bb_01_8219(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821A(runtime);
}


/* Block bb_01_821A at bank=01 addr=821A */
static void bb_01_821A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821B(runtime);
}


/* Block bb_01_821B at bank=01 addr=821B */
static void bb_01_821B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821C(runtime);
}


/* Block bb_01_821C at bank=01 addr=821C */
static void bb_01_821C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821D(runtime);
}


/* Block bb_01_821D at bank=01 addr=821D */
static void bb_01_821D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821E(runtime);
}


/* Block bb_01_821E at bank=01 addr=821E */
static void bb_01_821E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_821F(runtime);
}


/* Block bb_01_821F at bank=01 addr=821F */
static void bb_01_821F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8220(runtime);
}


/* Block bb_01_8220 at bank=01 addr=8220 */
static void bb_01_8220(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8221(runtime);
}


/* Block bb_01_8221 at bank=01 addr=8221 */
static void bb_01_8221(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8222(runtime);
}


/* Block bb_01_8222 at bank=01 addr=8222 */
static void bb_01_8222(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8223(runtime);
}


/* Block bb_01_8223 at bank=01 addr=8223 */
static void bb_01_8223(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8224(runtime);
}


/* Block bb_01_8224 at bank=01 addr=8224 */
static void bb_01_8224(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8225(runtime);
}


/* Block bb_01_8225 at bank=01 addr=8225 */
static void bb_01_8225(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8226(runtime);
}


/* Block bb_01_8226 at bank=01 addr=8226 */
static void bb_01_8226(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8227(runtime);
}


/* Block bb_01_8227 at bank=01 addr=8227 */
static void bb_01_8227(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8228(runtime);
}


/* Block bb_01_8228 at bank=01 addr=8228 */
static void bb_01_8228(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8229(runtime);
}


/* Block bb_01_8229 at bank=01 addr=8229 */
static void bb_01_8229(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822A(runtime);
}


/* Block bb_01_822A at bank=01 addr=822A */
static void bb_01_822A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822B(runtime);
}


/* Block bb_01_822B at bank=01 addr=822B */
static void bb_01_822B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822C(runtime);
}


/* Block bb_01_822C at bank=01 addr=822C */
static void bb_01_822C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822D(runtime);
}


/* Block bb_01_822D at bank=01 addr=822D */
static void bb_01_822D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822E(runtime);
}


/* Block bb_01_822E at bank=01 addr=822E */
static void bb_01_822E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_822F(runtime);
}


/* Block bb_01_822F at bank=01 addr=822F */
static void bb_01_822F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8230(runtime);
}


/* Block bb_01_8230 at bank=01 addr=8230 */
static void bb_01_8230(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8231(runtime);
}


/* Block bb_01_8231 at bank=01 addr=8231 */
static void bb_01_8231(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8232(runtime);
}


/* Block bb_01_8232 at bank=01 addr=8232 */
static void bb_01_8232(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8233(runtime);
}


/* Block bb_01_8233 at bank=01 addr=8233 */
static void bb_01_8233(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8234(runtime);
}


/* Block bb_01_8234 at bank=01 addr=8234 */
static void bb_01_8234(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8235(runtime);
}


/* Block bb_01_8235 at bank=01 addr=8235 */
static void bb_01_8235(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8236(runtime);
}


/* Block bb_01_8236 at bank=01 addr=8236 */
static void bb_01_8236(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8237(runtime);
}


/* Block bb_01_8237 at bank=01 addr=8237 */
static void bb_01_8237(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8238(runtime);
}


/* Block bb_01_8238 at bank=01 addr=8238 */
static void bb_01_8238(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8239(runtime);
}


/* Block bb_01_8239 at bank=01 addr=8239 */
static void bb_01_8239(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823A(runtime);
}


/* Block bb_01_823A at bank=01 addr=823A */
static void bb_01_823A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823B(runtime);
}


/* Block bb_01_823B at bank=01 addr=823B */
static void bb_01_823B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823C(runtime);
}


/* Block bb_01_823C at bank=01 addr=823C */
static void bb_01_823C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823D(runtime);
}


/* Block bb_01_823D at bank=01 addr=823D */
static void bb_01_823D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823E(runtime);
}


/* Block bb_01_823E at bank=01 addr=823E */
static void bb_01_823E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_823F(runtime);
}


/* Block bb_01_823F at bank=01 addr=823F */
static void bb_01_823F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8240(runtime);
}


/* Block bb_01_8240 at bank=01 addr=8240 */
static void bb_01_8240(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8241(runtime);
}


/* Block bb_01_8241 at bank=01 addr=8241 */
static void bb_01_8241(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8242(runtime);
}


/* Block bb_01_8242 at bank=01 addr=8242 */
static void bb_01_8242(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8243(runtime);
}


/* Block bb_01_8243 at bank=01 addr=8243 */
static void bb_01_8243(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8244(runtime);
}


/* Block bb_01_8244 at bank=01 addr=8244 */
static void bb_01_8244(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8245(runtime);
}


/* Block bb_01_8245 at bank=01 addr=8245 */
static void bb_01_8245(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8246(runtime);
}


/* Block bb_01_8246 at bank=01 addr=8246 */
static void bb_01_8246(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8247(runtime);
}


/* Block bb_01_8247 at bank=01 addr=8247 */
static void bb_01_8247(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8248(runtime);
}


/* Block bb_01_8248 at bank=01 addr=8248 */
static void bb_01_8248(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8249(runtime);
}


/* Block bb_01_8249 at bank=01 addr=8249 */
static void bb_01_8249(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824A(runtime);
}


/* Block bb_01_824A at bank=01 addr=824A */
static void bb_01_824A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824B(runtime);
}


/* Block bb_01_824B at bank=01 addr=824B */
static void bb_01_824B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824C(runtime);
}


/* Block bb_01_824C at bank=01 addr=824C */
static void bb_01_824C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824D(runtime);
}


/* Block bb_01_824D at bank=01 addr=824D */
static void bb_01_824D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824E(runtime);
}


/* Block bb_01_824E at bank=01 addr=824E */
static void bb_01_824E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_824F(runtime);
}


/* Block bb_01_824F at bank=01 addr=824F */
static void bb_01_824F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8250(runtime);
}


/* Block bb_01_8250 at bank=01 addr=8250 */
static void bb_01_8250(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8251(runtime);
}


/* Block bb_01_8251 at bank=01 addr=8251 */
static void bb_01_8251(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8252(runtime);
}


/* Block bb_01_8252 at bank=01 addr=8252 */
static void bb_01_8252(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8253(runtime);
}


/* Block bb_01_8253 at bank=01 addr=8253 */
static void bb_01_8253(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8254(runtime);
}


/* Block bb_01_8254 at bank=01 addr=8254 */
static void bb_01_8254(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8255(runtime);
}


/* Block bb_01_8255 at bank=01 addr=8255 */
static void bb_01_8255(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8256(runtime);
}


/* Block bb_01_8256 at bank=01 addr=8256 */
static void bb_01_8256(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8257(runtime);
}


/* Block bb_01_8257 at bank=01 addr=8257 */
static void bb_01_8257(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8258(runtime);
}


/* Block bb_01_8258 at bank=01 addr=8258 */
static void bb_01_8258(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8259(runtime);
}


/* Block bb_01_8259 at bank=01 addr=8259 */
static void bb_01_8259(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825A(runtime);
}


/* Block bb_01_825A at bank=01 addr=825A */
static void bb_01_825A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825B(runtime);
}


/* Block bb_01_825B at bank=01 addr=825B */
static void bb_01_825B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825C(runtime);
}


/* Block bb_01_825C at bank=01 addr=825C */
static void bb_01_825C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825D(runtime);
}


/* Block bb_01_825D at bank=01 addr=825D */
static void bb_01_825D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825E(runtime);
}


/* Block bb_01_825E at bank=01 addr=825E */
static void bb_01_825E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_825F(runtime);
}


/* Block bb_01_825F at bank=01 addr=825F */
static void bb_01_825F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8260(runtime);
}


/* Block bb_01_8260 at bank=01 addr=8260 */
static void bb_01_8260(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8261(runtime);
}


/* Block bb_01_8261 at bank=01 addr=8261 */
static void bb_01_8261(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8262(runtime);
}


/* Block bb_01_8262 at bank=01 addr=8262 */
static void bb_01_8262(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8263(runtime);
}


/* Block bb_01_8263 at bank=01 addr=8263 */
static void bb_01_8263(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8264(runtime);
}


/* Block bb_01_8264 at bank=01 addr=8264 */
static void bb_01_8264(SCV11Runtime* runtime) {
    /* ASL 1e78 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_01_8266(runtime);
}


/* Block bb_01_8266 at bank=01 addr=8266 */
static void bb_01_8266(SCV11Runtime* runtime) {
    /* BPL 1000 */
    /* BPL -> $8268 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x8268u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_8268(runtime);
    return;
}


/* Block bb_01_8268 at bank=01 addr=8268 */
static void bb_01_8268(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8269(runtime);
}


/* Block bb_01_8269 at bank=01 addr=8269 */
static void bb_01_8269(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_826A(runtime);
}


/* Block bb_01_826A at bank=01 addr=826A */
static void bb_01_826A(SCV11Runtime* runtime) {
    /* ASL 1e78 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_01_826C(runtime);
}


/* Block bb_01_826C at bank=01 addr=826C */
static void bb_01_826C(SCV11Runtime* runtime) {
    /* BPL 1000 */
    /* BPL -> $826E if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x826Eu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_826E(runtime);
    return;
}


/* Block bb_01_826E at bank=01 addr=826E */
static void bb_01_826E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_826F(runtime);
}


/* Block bb_01_826F at bank=01 addr=826F */
static void bb_01_826F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8270(runtime);
}


/* Block bb_01_8270 at bank=01 addr=8270 */
static void bb_01_8270(SCV11Runtime* runtime) {
    /* ASL 1e78 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_01_8272(runtime);
}


/* Block bb_01_8272 at bank=01 addr=8272 */
static void bb_01_8272(SCV11Runtime* runtime) {
    /* BPL 1000 */
    /* BPL -> $8274 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x8274u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_8274(runtime);
    return;
}


/* Block bb_01_8274 at bank=01 addr=8274 */
static void bb_01_8274(SCV11Runtime* runtime) {
    /* STZ dp 9e01c0 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_01_8277(runtime);
}


/* Block bb_01_8277 at bank=01 addr=8277 */
static void bb_01_8277(SCV11Runtime* runtime) {
    /* AND (ind,S) 03800100 */
    /* TODO: AND (ind,S) */
    runtime->route_failed = 1; return;
    bb_01_827B(runtime);
}


/* Block bb_01_827B at bank=01 addr=827B */
static void bb_01_827B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_827C(runtime);
}


/* Block bb_01_827C at bank=01 addr=827C */
static void bb_01_827C(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_827D(runtime);
}


/* Block bb_01_827D at bank=01 addr=827D */
static void bb_01_827D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_827E(runtime);
}


/* Block bb_01_827E at bank=01 addr=827E */
static void bb_01_827E(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_827F(runtime);
}


/* Block bb_01_827F at bank=01 addr=827F */
static void bb_01_827F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8280(runtime);
}


/* Block bb_01_8280 at bank=01 addr=8280 */
static void bb_01_8280(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8281(runtime);
}


/* Block bb_01_8281 at bank=01 addr=8281 */
static void bb_01_8281(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8282(runtime);
}


/* Block bb_01_8282 at bank=01 addr=8282 */
static void bb_01_8282(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8283(runtime);
}


/* Block bb_01_8283 at bank=01 addr=8283 */
static void bb_01_8283(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8284(runtime);
}


/* Block bb_01_8284 at bank=01 addr=8284 */
static void bb_01_8284(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8285(runtime);
}


/* Block bb_01_8285 at bank=01 addr=8285 */
static void bb_01_8285(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8286(runtime);
}


/* Block bb_01_8286 at bank=01 addr=8286 */
static void bb_01_8286(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8287(runtime);
}


/* Block bb_01_8287 at bank=01 addr=8287 */
static void bb_01_8287(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8288(runtime);
}


/* Block bb_01_8288 at bank=01 addr=8288 */
static void bb_01_8288(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8289(runtime);
}


/* Block bb_01_8289 at bank=01 addr=8289 */
static void bb_01_8289(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_828A(runtime);
}


/* Block bb_01_828A at bank=01 addr=828A */
static void bb_01_828A(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_828B(runtime);
}


/* Block bb_01_828B at bank=01 addr=828B */
static void bb_01_828B(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_828C(runtime);
}


/* Block bb_01_828C at bank=01 addr=828C */
static void bb_01_828C(SCV11Runtime* runtime) {
    /* BRA 8001 */
    /* BRA $01 -> $828F */
    runtime->machine.cpu.pc = 0x828Fu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_01_828F(runtime);
    return;
}


/* Block bb_01_828F at bank=01 addr=828F */
static void bb_01_828F(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8290(runtime);
}


/* Block bb_01_8290 at bank=01 addr=8290 */
static void bb_01_8290(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8291(runtime);
}


/* Block bb_01_8291 at bank=01 addr=8291 */
static void bb_01_8291(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8292(runtime);
}


/* Block bb_01_8292 at bank=01 addr=8292 */
static void bb_01_8292(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8293(runtime);
}


/* Block bb_01_8293 at bank=01 addr=8293 */
static void bb_01_8293(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8294(runtime);
}


/* Block bb_01_8294 at bank=01 addr=8294 */
static void bb_01_8294(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8295(runtime);
}


/* Block bb_01_8295 at bank=01 addr=8295 */
static void bb_01_8295(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_8296(runtime);
}


/* Block bb_01_8296 at bank=01 addr=8296 */
static void bb_01_8296(SCV11Runtime* runtime) {
    /* CPY #imm c003 */
    /* TODO: CPY #imm */
    runtime->route_failed = 1; return;
    bb_01_8298(runtime);
}


/* Block bb_01_8298 at bank=01 addr=8298 */
static void bb_01_8298(SCV11Runtime* runtime) {
    /* ASL 1e78 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_01_829A(runtime);
}


/* Block bb_01_829A at bank=01 addr=829A */
static void bb_01_829A(SCV11Runtime* runtime) {
    /* BPL 1000 */
    /* BPL -> $829C if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x829Cu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_829C(runtime);
    return;
}


/* Block bb_01_829C at bank=01 addr=829C */
static void bb_01_829C(SCV11Runtime* runtime) {
    /* STZ dp 9e0280 */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_01_829F(runtime);
}


/* Block bb_01_829F at bank=01 addr=829F */
static void bb_01_829F(SCV11Runtime* runtime) {
    /* ROR A 6a */
    /* TODO: ROR A */
    runtime->route_failed = 1; return;
    bb_01_82A0(runtime);
}


/* Block bb_01_82A0 at bank=01 addr=82A0 */
static void bb_01_82A0(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A1(runtime);
}


/* Block bb_01_82A1 at bank=01 addr=82A1 */
static void bb_01_82A1(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A2(runtime);
}


/* Block bb_01_82A2 at bank=01 addr=82A2 */
static void bb_01_82A2(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A3(runtime);
}


/* Block bb_01_82A3 at bank=01 addr=82A3 */
static void bb_01_82A3(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A4(runtime);
}


/* Block bb_01_82A4 at bank=01 addr=82A4 */
static void bb_01_82A4(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A5(runtime);
}


/* Block bb_01_82A5 at bank=01 addr=82A5 */
static void bb_01_82A5(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A6(runtime);
}


/* Block bb_01_82A6 at bank=01 addr=82A6 */
static void bb_01_82A6(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A7(runtime);
}


/* Block bb_01_82A7 at bank=01 addr=82A7 */
static void bb_01_82A7(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82A8(runtime);
}


/* Block bb_01_82A8 at bank=01 addr=82A8 */
static void bb_01_82A8(SCV11Runtime* runtime) {
    /* STZ dp 9e019e */
    /* TODO: STZ dp */
    runtime->route_failed = 1; return;
    bb_01_82AB(runtime);
}


/* Block bb_01_82AB at bank=01 addr=82AB */
static void bb_01_82AB(SCV11Runtime* runtime) {
    /* ORA (ind,X) 019e01005000 */
    /* TODO: ORA (ind,X) */
    runtime->route_failed = 1; return;
    bb_01_82B1(runtime);
}


/* Block bb_01_82B1 at bank=01 addr=82B1 */
static void bb_01_82B1(SCV11Runtime* runtime) {
    /* BVC 5000 */
    /* BVC -> $82B3 if V=0 */
    if ((runtime->machine.cpu.status & 0x40) == 0) {
        runtime->machine.cpu.pc = 0x82B3u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_82B3(runtime);
    return;
}


/* Block bb_01_82B3 at bank=01 addr=82B3 */
static void bb_01_82B3(SCV11Runtime* runtime) {
    /* BVC 5000 */
    /* BVC -> $82B5 if V=0 */
    if ((runtime->machine.cpu.status & 0x40) == 0) {
        runtime->machine.cpu.pc = 0x82B5u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_01_82B5(runtime);
    return;
}


/* Block bb_01_82B5 at bank=01 addr=82B5 */
static void bb_01_82B5(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82B6(runtime);
}


/* Block bb_01_82B6 at bank=01 addr=82B6 */
static void bb_01_82B6(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82B7(runtime);
}


/* Block bb_01_82B7 at bank=01 addr=82B7 */
static void bb_01_82B7(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82B8(runtime);
}


/* Block bb_01_82B8 at bank=01 addr=82B8 */
static void bb_01_82B8(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82B9(runtime);
}


/* Block bb_01_82B9 at bank=01 addr=82B9 */
static void bb_01_82B9(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BA(runtime);
}


/* Block bb_01_82BA at bank=01 addr=82BA */
static void bb_01_82BA(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BB(runtime);
}


/* Block bb_01_82BB at bank=01 addr=82BB */
static void bb_01_82BB(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BC(runtime);
}


/* Block bb_01_82BC at bank=01 addr=82BC */
static void bb_01_82BC(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BD(runtime);
}


/* Block bb_01_82BD at bank=01 addr=82BD */
static void bb_01_82BD(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BE(runtime);
}


/* Block bb_01_82BE at bank=01 addr=82BE */
static void bb_01_82BE(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82BF(runtime);
}


/* Block bb_01_82BF at bank=01 addr=82BF */
static void bb_01_82BF(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82C0(runtime);
}


/* Block bb_01_82C0 at bank=01 addr=82C0 */
static void bb_01_82C0(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82C1(runtime);
}


/* Block bb_01_82C1 at bank=01 addr=82C1 */
static void bb_01_82C1(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82C2(runtime);
}


/* Block bb_01_82C2 at bank=01 addr=82C2 */
static void bb_01_82C2(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82C3(runtime);
}


/* Block bb_01_82C3 at bank=01 addr=82C3 */
static void bb_01_82C3(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_01_82C4(runtime);
}


/* Block bb_01_82C4 at bank=01 addr=82C4 */
static void bb_01_82C4(SCV11Runtime* runtime) {
    /* DEC abs ce396b */
    /* TODO: DEC abs */
    runtime->route_failed = 1; return;
    bb_01_82C7(runtime);
}


/* Block bb_01_82C7 at bank=01 addr=82C7 */
static void bb_01_82C7(SCV11Runtime* runtime) {
    /* AND abs 2de71c */
    /* TODO: AND abs */
    runtime->route_failed = 1; return;
    bb_01_82CA(runtime);
}


/* Block bb_01_82CA at bank=01 addr=82CA */
static void bb_01_82CA(SCV11Runtime* runtime) {
    /* RTI 40 */
    /* RTI */
    {
        uint8_t status = stack_pop(runtime);
        uint16_t pc_lo = stack_pop(runtime);
        uint16_t pc_hi = stack_pop(runtime);
        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo);
        runtime->machine.cpu.status = (status & ~0x30) | 0x20; /* clear B, set U */
        runtime->scheduler.cpu_instructions += 6;
        runtime->scheduler.master_clock += 6;
        return;
    }
    return;
}


/* Block bb_02_81A2 at bank=02 addr=81A2 */
static void bb_02_81A2(SCV11Runtime* runtime) {
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81A3(runtime);
}


/* Block bb_02_81A3 at bank=02 addr=81A3 */
static void bb_02_81A3(SCV11Runtime* runtime) {
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81A4(runtime);
}


/* Block bb_02_81A4 at bank=02 addr=81A4 */
static void bb_02_81A4(SCV11Runtime* runtime) {
    /* BIT abs 3c007e */
    /* TODO: BIT abs */
    runtime->route_failed = 1; return;
    bb_02_81A7(runtime);
}


/* Block bb_02_81A7 at bank=02 addr=81A7 */
static void bb_02_81A7(SCV11Runtime* runtime) {
    /* CLC 18 */
    /* CLC */
    runtime->machine.cpu.status &= ~0x01;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81A8(runtime);
}


/* Block bb_02_81A8 at bank=02 addr=81A8 */
static void bb_02_81A8(SCV11Runtime* runtime) {
    /* CPX abs ec8ce6 */
    /* TODO: CPX abs */
    runtime->route_failed = 1; return;
    /* BRA 80fc */
    /* BRA $FFFC -> $81A9 */
    runtime->machine.cpu.pc = 0x81A9u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81A9(runtime);
    return;
}


/* Block bb_02_81A9 at bank=02 addr=81A9 */
static void bb_02_81A9(SCV11Runtime* runtime) {
    /* STY abs 8ce680 */
    /* TODO: STY abs */
    runtime->route_failed = 1; return;
    /* INC dp fcc078 */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* MVD 7c */
    /* MVD - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* INC abs fe98ee */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* INC abs ee88fc */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81B3 */
    runtime->machine.cpu.pc = 0x81B3u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81B3(runtime);
    return;
}


/* Block bb_02_81AB at bank=02 addr=81AB */
static void bb_02_81AB(SCV11Runtime* runtime) {
    /* BRA 80fc */
    /* BRA $FFFC -> $81A9 */
    runtime->machine.cpu.pc = 0x81A9u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81A9(runtime);
    return;
}


/* Block bb_02_81AC at bank=02 addr=81AC */
static void bb_02_81AC(SCV11Runtime* runtime) {
    /* INC dp fcc078 */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* MVD 7c */
    /* MVD - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* INC abs fe98ee */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* INC abs ee88fc */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81B3 */
    runtime->machine.cpu.pc = 0x81B3u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81B3(runtime);
    return;
}


/* Block bb_02_81AF at bank=02 addr=81AF */
static void bb_02_81AF(SCV11Runtime* runtime) {
    /* SEI 78 */
    /* SEI - Disable Interrupts */
    runtime->machine.cpu.status |= 0x04;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81B0(runtime);
}


/* Block bb_02_81B0 at bank=02 addr=81B0 */
static void bb_02_81B0(SCV11Runtime* runtime) {
    /* MVD 7c */
    /* MVD - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_02_81B1(runtime);
}


/* Block bb_02_81B1 at bank=02 addr=81B1 */
static void bb_02_81B1(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_02_81B2(runtime);
}


/* Block bb_02_81B2 at bank=02 addr=81B2 */
static void bb_02_81B2(SCV11Runtime* runtime) {
    /* INC abs fe98ee */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* INC abs ee88fc */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81B3 */
    runtime->machine.cpu.pc = 0x81B3u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81B3(runtime);
    return;
}


/* Block bb_02_81B3 at bank=02 addr=81B3 */
static void bb_02_81B3(SCV11Runtime* runtime) {
    /* TYA 98 */
    /* TYA */
    runtime->machine.cpu.a = runtime->machine.cpu.y;
    if (runtime->machine.cpu.a & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.a == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81B4(runtime);
}


/* Block bb_02_81B4 at bank=02 addr=81B4 */
static void bb_02_81B4(SCV11Runtime* runtime) {
    /* INC abs ee88ee */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* INC dp fc80f8 */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* EOR 7e00 */
    /* EOR */
    runtime->route_failed = 1; return;
    /* INC dp fc9cfc */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81BB */
    runtime->machine.cpu.pc = 0x81BBu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81BB(runtime);
    return;
}


/* Block bb_02_81B5 at bank=02 addr=81B5 */
static void bb_02_81B5(SCV11Runtime* runtime) {
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81B6(runtime);
}


/* Block bb_02_81B6 at bank=02 addr=81B6 */
static void bb_02_81B6(SCV11Runtime* runtime) {
    /* INC abs ee88fc */
    /* TODO: INC abs */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81B3 */
    runtime->machine.cpu.pc = 0x81B3u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81B3(runtime);
    return;
}


/* Block bb_02_81B7 at bank=02 addr=81B7 */
static void bb_02_81B7(SCV11Runtime* runtime) {
    /* DEY 88 */
    /* DEY */
    runtime->machine.cpu.y = (runtime->machine.cpu.y - 1) & 0xFFFF;
    if (runtime->machine.cpu.y & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.y == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81B8(runtime);
}


/* Block bb_02_81B8 at bank=02 addr=81B8 */
static void bb_02_81B8(SCV11Runtime* runtime) {
    /* INC dp fc80f8 */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    /* EOR 7e00 */
    /* EOR */
    runtime->route_failed = 1; return;
    /* INC dp fc9cfc */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81BB */
    runtime->machine.cpu.pc = 0x81BBu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81BB(runtime);
    return;
}


/* Block bb_02_81B9 at bank=02 addr=81B9 */
static void bb_02_81B9(SCV11Runtime* runtime) {
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81B3 */
    runtime->machine.cpu.pc = 0x81B3u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81B3(runtime);
    return;
}


/* Block bb_02_81BB at bank=02 addr=81BB */
static void bb_02_81BB(SCV11Runtime* runtime) {
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_02_81BC(runtime);
}


/* Block bb_02_81BC at bank=02 addr=81BC */
static void bb_02_81BC(SCV11Runtime* runtime) {
    /* EOR 7e00 */
    /* EOR */
    runtime->route_failed = 1; return;
    bb_02_81BE(runtime);
}


/* Block bb_02_81BE at bank=02 addr=81BE */
static void bb_02_81BE(SCV11Runtime* runtime) {
    /* INC dp fc9cfc */
    /* TODO: INC dp */
    runtime->route_failed = 1; return;
    bb_02_81C1(runtime);
}


/* Block bb_02_81C1 at bank=02 addr=81C1 */
static void bb_02_81C1(SCV11Runtime* runtime) {
    /* BRA 80f8 */
    /* BRA $FFF8 -> $81BB */
    runtime->machine.cpu.pc = 0x81BBu;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_02_81BB(runtime);
    return;
}


/* Block bb_07_800C at bank=07 addr=800C */
static void bb_07_800C(SCV11Runtime* runtime) {
    /* TCD 3b */
    /* TCD - Transfer A to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.a;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_07_800D(runtime);
}


/* Block bb_07_800D at bank=07 addr=800D */
static void bb_07_800D(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_07_800E(runtime);
}


/* Block bb_07_800E at bank=07 addr=800E */
static void bb_07_800E(SCV11Runtime* runtime) {
    /* WDM 4280 */
    /* WDM - Reserved */
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_07_8010(runtime);
}


/* Block bb_07_8010 at bank=07 addr=8010 */
static void bb_07_8010(SCV11Runtime* runtime) {
    /* RTS 60 */
    /* RTS */
    {
        uint16_t pc_lo = stack_pop(runtime);
        uint16_t pc_hi = stack_pop(runtime);
        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo) + 1;
        runtime->scheduler.cpu_instructions += 6;
        runtime->scheduler.master_clock += 6;
        return;
    }
    return;
}


/* Block bb_07_82B7 at bank=07 addr=82B7 */
static void bb_07_82B7(SCV11Runtime* runtime) {
    /* BRA 8060 */
    /* BRA $60 -> $8319 */
    runtime->machine.cpu.pc = 0x8319u;
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    return;
    bb_07_8319(runtime);
    return;
}


/* Block bb_07_8319 at bank=07 addr=8319 */
static void bb_07_8319(SCV11Runtime* runtime) {
    /* SED f8 */
    /* SED - Set Decimal Mode */
    runtime->machine.cpu.status |= 0x08;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_07_831A(runtime);
}


/* Block bb_07_831A at bank=07 addr=831A */
static void bb_07_831A(SCV11Runtime* runtime) {
    /* RTS 60 */
    /* RTS */
    {
        uint16_t pc_lo = stack_pop(runtime);
        uint16_t pc_hi = stack_pop(runtime);
        runtime->machine.cpu.pc = (uint16_t)((pc_hi << 8) | pc_lo) + 1;
        runtime->scheduler.cpu_instructions += 6;
        runtime->scheduler.master_clock += 6;
        return;
    }
    return;
}


/* Block bb_0C_8177 at bank=0C addr=8177 */
static void bb_0C_8177(SCV11Runtime* runtime) {
    /* ROL 3f10 */
    /* ROL memory - stub */
    runtime->route_failed = 1; return;
    bb_0C_8179(runtime);
}


/* Block bb_0C_8179 at bank=0C addr=8179 */
static void bb_0C_8179(SCV11Runtime* runtime) {
    /* PHX da */
    /* PHX */
    stack_push(runtime, runtime->machine.cpu.x);
    runtime->scheduler.cpu_instructions += 3;
    runtime->scheduler.master_clock += 3;
    bb_0C_817A(runtime);
}


/* Block bb_0C_817A at bank=0C addr=817A */
static void bb_0C_817A(SCV11Runtime* runtime) {
    /* ORA (ind,X) 0111ba191210 */
    /* TODO: ORA (ind,X) */
    runtime->route_failed = 1; return;
    bb_0C_8180(runtime);
}


/* Block bb_0C_8180 at bank=0C addr=8180 */
static void bb_0C_8180(SCV11Runtime* runtime) {
    /* ASL 1e33 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_0C_8182(runtime);
}


/* Block bb_0C_8182 at bank=0C addr=8182 */
static void bb_0C_8182(SCV11Runtime* runtime) {
    /* CPY #imm c00e */
    /* TODO: CPY #imm */
    runtime->route_failed = 1; return;
    bb_0C_8184(runtime);
}


/* Block bb_0C_8184 at bank=0C addr=8184 */
static void bb_0C_8184(SCV11Runtime* runtime) {
    /* EOR #imm 49ce */
    /* TODO: EOR #imm */
    runtime->route_failed = 1; return;
    bb_0C_8186(runtime);
}


/* Block bb_0C_8186 at bank=0C addr=8186 */
static void bb_0C_8186(SCV11Runtime* runtime) {
    /* AND (ind,S),Y 330c101f1f */
    /* TODO: AND (ind,S),Y */
    runtime->route_failed = 1; return;
    bb_0C_818B(runtime);
}


/* Block bb_0C_818B at bank=0C addr=818B */
static void bb_0C_818B(SCV11Runtime* runtime) {
    /* ASL 0e11 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_0C_818D(runtime);
}


/* Block bb_0C_818D at bank=0C addr=818D */
static void bb_0C_818D(SCV11Runtime* runtime) {
    /* ASL 1fba */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_0C_818F(runtime);
}


/* Block bb_0C_818F at bank=0C addr=818F */
static void bb_0C_818F(SCV11Runtime* runtime) {
    /* CPX abs ec155d */
    /* TODO: CPX abs */
    runtime->route_failed = 1; return;
    bb_0C_8192(runtime);
}


/* Block bb_0C_8192 at bank=0C addr=8192 */
static void bb_0C_8192(SCV11Runtime* runtime) {
    /* CPX #imm e0ba */
    /* TODO: CPX #imm */
    runtime->route_failed = 1; return;
    bb_0C_8194(runtime);
}


/* Block bb_0C_8194 at bank=0C addr=8194 */
static void bb_0C_8194(SCV11Runtime* runtime) {
    /* MVN 44 */
    /* TODO: MVN */
    runtime->route_failed = 1; return;
    bb_0C_8195(runtime);
}


/* Block bb_0C_8195 at bank=0C addr=8195 */
static void bb_0C_8195(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_0C_8196(runtime);
}


/* Block bb_0C_8196 at bank=0C addr=8196 */
static void bb_0C_8196(SCV11Runtime* runtime) {
    /* TSD 04 */
    /* TSD - Transfer Stack Pointer to Direct Page */
    runtime->machine.cpu.d = runtime->machine.cpu.sp;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_0C_8197(runtime);
}


/* Block bb_0C_8197 at bank=0C addr=8197 */
static void bb_0C_8197(SCV11Runtime* runtime) {
    /* TSX ba */
    /* TSX */
    runtime->machine.cpu.x = runtime->machine.cpu.sp;
    if (runtime->machine.cpu.x & 0x80) runtime->machine.cpu.status |= 0x80; else runtime->machine.cpu.status &= ~0x80;
    if (runtime->machine.cpu.x == 0) runtime->machine.cpu.status |= 0x02; else runtime->machine.cpu.status &= ~0x02;
    runtime->scheduler.cpu_instructions += 2;
    runtime->scheduler.master_clock += 2;
    bb_0C_8198(runtime);
}


/* Block bb_0C_8198 at bank=0C addr=8198 */
static void bb_0C_8198(SCV11Runtime* runtime) {
    /* BPL 100b */
    /* BPL -> $81A5 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81A5u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81A5(runtime);
    return;
}


/* Block bb_0C_81A2 at bank=0C addr=81A2 */
static void bb_0C_81A2(SCV11Runtime* runtime) {
    /* ROR 6e0c */
    /* ROR memory */
    runtime->route_failed = 1;  /* TODO: ROR memory */
    return;
    bb_0C_81A4(runtime);
}


/* Block bb_0C_81A4 at bank=0C addr=81A4 */
static void bb_0C_81A4(SCV11Runtime* runtime) {
    /* TRB dp 14f2fe */
    /* TODO: TRB dp */
    runtime->route_failed = 1; return;
    /* ORA (ind,X) 011fb6119aea */
    /* TODO: ORA (ind,X) */
    runtime->route_failed = 1; return;
    /* BEQ f010 */
    /* BEQ -> $81BF if Z=1 */
    if ((runtime->machine.cpu.status & 0x02) != 0) {
        runtime->machine.cpu.pc = 0x81BFu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81BF(runtime);
    return;
}


/* Block bb_0C_81A5 at bank=0C addr=81A5 */
static void bb_0C_81A5(SCV11Runtime* runtime) {
    /* SBC dp f2fe01 */
    /* TODO: SBC dp */
    runtime->route_failed = 1; return;
    /* ASL 1fb6 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    /* ORA (ind,S),Y 119aeaf010 */
    /* TODO: ORA (ind,S),Y */
    runtime->route_failed = 1; return;
    /* NEG dp 542610 */
    /* TODO: NEG dp */
    runtime->route_failed = 1; return;
    /* LDX abs ae1e10 */
    /* TODO: LDX abs */
    runtime->route_failed = 1; return;
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* BPL 1009 */
    /* BPL -> $81C1 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81C1u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81C1(runtime);
    return;
}


/* Block bb_0C_81A7 at bank=0C addr=81A7 */
static void bb_0C_81A7(SCV11Runtime* runtime) {
    /* ORA (ind,X) 011fb6119aea */
    /* TODO: ORA (ind,X) */
    runtime->route_failed = 1; return;
    /* BEQ f010 */
    /* BEQ -> $81BF if Z=1 */
    if ((runtime->machine.cpu.status & 0x02) != 0) {
        runtime->machine.cpu.pc = 0x81BFu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81BF(runtime);
    return;
}


/* Block bb_0C_81A8 at bank=0C addr=81A8 */
static void bb_0C_81A8(SCV11Runtime* runtime) {
    /* ASL 1fb6 */
    /* ASL memory stub */
    runtime->route_failed = 1; return;
    bb_0C_81AA(runtime);
}


/* Block bb_0C_81AA at bank=0C addr=81AA */
static void bb_0C_81AA(SCV11Runtime* runtime) {
    /* ORA (ind,S),Y 119aeaf010 */
    /* TODO: ORA (ind,S),Y */
    runtime->route_failed = 1; return;
    /* NEG dp 542610 */
    /* TODO: NEG dp */
    runtime->route_failed = 1; return;
    /* LDX abs ae1e10 */
    /* TODO: LDX abs */
    runtime->route_failed = 1; return;
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    /* BPL 1009 */
    /* BPL -> $81C1 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81C1u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81C1(runtime);
    return;
}


/* Block bb_0C_81AD at bank=0C addr=81AD */
static void bb_0C_81AD(SCV11Runtime* runtime) {
    /* BEQ f010 */
    /* BEQ -> $81BF if Z=1 */
    if ((runtime->machine.cpu.status & 0x02) != 0) {
        runtime->machine.cpu.pc = 0x81BFu;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81BF(runtime);
    return;
}


/* Block bb_0C_81AF at bank=0C addr=81AF */
static void bb_0C_81AF(SCV11Runtime* runtime) {
    /* NEG dp 542610 */
    /* TODO: NEG dp */
    runtime->route_failed = 1; return;
    bb_0C_81B2(runtime);
}


/* Block bb_0C_81B2 at bank=0C addr=81B2 */
static void bb_0C_81B2(SCV11Runtime* runtime) {
    /* LDX abs ae1e10 */
    /* TODO: LDX abs */
    runtime->route_failed = 1; return;
    bb_0C_81B5(runtime);
}


/* Block bb_0C_81B5 at bank=0C addr=81B5 */
static void bb_0C_81B5(SCV11Runtime* runtime) {
    /* BRK 00 */
    /* BRK - software interrupt */
    {
        uint8_t status = runtime->machine.cpu.status | 0x10; /* B flag */
        stack_push(runtime, (uint8_t)((runtime->machine.cpu.pc + 2) >> 8));
        stack_push(runtime, (uint8_t)(runtime->machine.cpu.pc + 2));
        stack_push(runtime, status);
        runtime->machine.cpu.status |= 0x14; /* I and B flags */
        uint16_t brk_pc = rom_read(runtime, 0xFFFE) | ((uint16_t)rom_read(runtime, 0xFFFF) << 8);
        runtime->machine.cpu.pc = brk_pc;
        runtime->machine.cpu.bank = 0x00;
        runtime->scheduler.cpu_instructions += 7;
        runtime->scheduler.master_clock += 8;
        return;
    }
    bb_0C_81B6(runtime);
}


/* Block bb_0C_81B6 at bank=0C addr=81B6 */
static void bb_0C_81B6(SCV11Runtime* runtime) {
    /* BPL 1009 */
    /* BPL -> $81C1 if N=0 */
    if ((runtime->machine.cpu.status & 0x80) == 0) {
        runtime->machine.cpu.pc = 0x81C1u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_81C1(runtime);
    return;
}


/* Block bb_0C_81BF at bank=0C addr=81BF */
static void bb_0C_81BF(SCV11Runtime* runtime) {
    /* CPX dp e433e0 */
    /* TODO: CPX dp */
    runtime->route_failed = 1; return;
    /* MVA 43 */
    /* MVA - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    /* BMI 30b2 */
    /* BMI -> $8177 if N=1 */
    if ((runtime->machine.cpu.status & 0x80) != 0) {
        runtime->machine.cpu.pc = 0x8177u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_8177(runtime);
    return;
}


/* Block bb_0C_81C1 at bank=0C addr=81C1 */
static void bb_0C_81C1(SCV11Runtime* runtime) {
    /* CPX #imm e043 */
    /* TODO: CPX #imm */
    runtime->route_failed = 1; return;
    /* BMI 30b2 */
    /* BMI -> $8177 if N=1 */
    if ((runtime->machine.cpu.status & 0x80) != 0) {
        runtime->machine.cpu.pc = 0x8177u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_8177(runtime);
    return;
}


/* Block bb_0C_81C2 at bank=0C addr=81C2 */
static void bb_0C_81C2(SCV11Runtime* runtime) {
    /* MVA 43 */
    /* MVA - nop */
    runtime->scheduler.cpu_instructions += 4;
    runtime->scheduler.master_clock += 4;
    bb_0C_81C3(runtime);
}


/* Block bb_0C_81C3 at bank=0C addr=81C3 */
static void bb_0C_81C3(SCV11Runtime* runtime) {
    /* BMI 30b2 */
    /* BMI -> $8177 if N=1 */
    if ((runtime->machine.cpu.status & 0x80) != 0) {
        runtime->machine.cpu.pc = 0x8177u;
        runtime->scheduler.cpu_instructions += 4;
        runtime->scheduler.master_clock += 4;
    } else {
        runtime->scheduler.cpu_instructions += 2;
        runtime->scheduler.master_clock += 2;
    }
    return;
    bb_0C_8177(runtime);
    return;
}


/* Dispatch table */
typedef void (*BlockFunc)(SCV11Runtime*);
static const struct {
    uint16_t pc;
    uint16_t bank;
    BlockFunc func;
} dispatch_table[] = {
    { 0x2020, 0x00, bb_00_2020 },
    { 0x2025, 0x00, bb_00_2025 },
    { 0x202D, 0x00, bb_00_202D },
    { 0x2035, 0x00, bb_00_2035 },
    { 0x203A, 0x00, bb_00_203A },
    { 0x203F, 0x00, bb_00_203F },
    { 0x204A, 0x00, bb_00_204A },
    { 0x204F, 0x00, bb_00_204F },
    { 0x2057, 0x00, bb_00_2057 },
    { 0x205F, 0x00, bb_00_205F },
    { 0x2061, 0x00, bb_00_2061 },
    { 0x2063, 0x00, bb_00_2063 },
    { 0x2065, 0x00, bb_00_2065 },
    { 0x2067, 0x00, bb_00_2067 },
    { 0x2069, 0x00, bb_00_2069 },
    { 0x206B, 0x00, bb_00_206B },
    { 0x206D, 0x00, bb_00_206D },
    { 0x206F, 0x00, bb_00_206F },
    { 0x2071, 0x00, bb_00_2071 },
    { 0x2073, 0x00, bb_00_2073 },
    { 0x2075, 0x00, bb_00_2075 },
    { 0x2077, 0x00, bb_00_2077 },
    { 0x2079, 0x00, bb_00_2079 },
    { 0x207B, 0x00, bb_00_207B },
    { 0x207D, 0x00, bb_00_207D },
    { 0x207F, 0x00, bb_00_207F },
    { 0x2087, 0x00, bb_00_2087 },
    { 0x208F, 0x00, bb_00_208F },
    { 0x2091, 0x00, bb_00_2091 },
    { 0x2093, 0x00, bb_00_2093 },
    { 0x2095, 0x00, bb_00_2095 },
    { 0x2097, 0x00, bb_00_2097 },
    { 0x2099, 0x00, bb_00_2099 },
    { 0x209B, 0x00, bb_00_209B },
    { 0x209D, 0x00, bb_00_209D },
    { 0x7FC2, 0x00, bb_00_7FC2 },
    { 0x7FC4, 0x00, bb_00_7FC4 },
    { 0x7FC6, 0x00, bb_00_7FC6 },
    { 0x800C, 0x00, bb_00_800C },
    { 0x800F, 0x00, bb_00_800F },
    { 0x8010, 0x00, bb_00_8010 },
    { 0x8011, 0x00, bb_00_8011 },
    { 0x8012, 0x00, bb_00_8012 },
    { 0x8013, 0x00, bb_00_8013 },
    { 0x8015, 0x00, bb_00_8015 },
    { 0x8016, 0x00, bb_00_8016 },
    { 0x8017, 0x00, bb_00_8017 },
    { 0x8018, 0x00, bb_00_8018 },
    { 0x8019, 0x00, bb_00_8019 },
    { 0x801C, 0x00, bb_00_801C },
    { 0x801F, 0x00, bb_00_801F },
    { 0x8020, 0x00, bb_00_8020 },
    { 0x8022, 0x00, bb_00_8022 },
    { 0x8024, 0x00, bb_00_8024 },
    { 0x8025, 0x00, bb_00_8025 },
    { 0x8026, 0x00, bb_00_8026 },
    { 0x8031, 0x00, bb_00_8031 },
    { 0x8033, 0x00, bb_00_8033 },
    { 0x81A2, 0x00, bb_00_81A2 },
    { 0x81A7, 0x00, bb_00_81A7 },
    { 0x81AA, 0x00, bb_00_81AA },
    { 0x81AB, 0x00, bb_00_81AB },
    { 0x81AC, 0x00, bb_00_81AC },
    { 0x81AD, 0x00, bb_00_81AD },
    { 0x81AE, 0x00, bb_00_81AE },
    { 0x81B0, 0x00, bb_00_81B0 },
    { 0x81B1, 0x00, bb_00_81B1 },
    { 0x81B2, 0x00, bb_00_81B2 },
    { 0x81B3, 0x00, bb_00_81B3 },
    { 0x81B4, 0x00, bb_00_81B4 },
    { 0x81B7, 0x00, bb_00_81B7 },
    { 0x81BC, 0x00, bb_00_81BC },
    { 0x81BD, 0x00, bb_00_81BD },
    { 0x81BE, 0x00, bb_00_81BE },
    { 0x81C0, 0x00, bb_00_81C0 },
    { 0x81C1, 0x00, bb_00_81C1 },
    { 0x81C6, 0x00, bb_00_81C6 },
    { 0x81C7, 0x00, bb_00_81C7 },
    { 0x81C9, 0x00, bb_00_81C9 },
    { 0x81CA, 0x00, bb_00_81CA },
    { 0x81D0, 0x00, bb_00_81D0 },
    { 0x81D6, 0x00, bb_00_81D6 },
    { 0x81DC, 0x00, bb_00_81DC },
    { 0x81DF, 0x00, bb_00_81DF },
    { 0x81E2, 0x00, bb_00_81E2 },
    { 0x81E3, 0x00, bb_00_81E3 },
    { 0x81E6, 0x00, bb_00_81E6 },
    { 0x81E9, 0x00, bb_00_81E9 },
    { 0x81EC, 0x00, bb_00_81EC },
    { 0x81EE, 0x00, bb_00_81EE },
    { 0x81EF, 0x00, bb_00_81EF },
    { 0x81F0, 0x00, bb_00_81F0 },
    { 0x82B7, 0x00, bb_00_82B7 },
    { 0x82B8, 0x00, bb_00_82B8 },
    { 0x82B9, 0x00, bb_00_82B9 },
    { 0x82BC, 0x00, bb_00_82BC },
    { 0x82BD, 0x00, bb_00_82BD },
    { 0x82C0, 0x00, bb_00_82C0 },
    { 0x82C3, 0x00, bb_00_82C3 },
    { 0x82C4, 0x00, bb_00_82C4 },
    { 0x82C6, 0x00, bb_00_82C6 },
    { 0x82C9, 0x00, bb_00_82C9 },
    { 0x82CB, 0x00, bb_00_82CB },
    { 0x82CC, 0x00, bb_00_82CC },
    { 0x82CD, 0x00, bb_00_82CD },
    { 0x82CF, 0x00, bb_00_82CF },
    { 0x82D0, 0x00, bb_00_82D0 },
    { 0x82D1, 0x00, bb_00_82D1 },
    { 0x82D2, 0x00, bb_00_82D2 },
    { 0x82D3, 0x00, bb_00_82D3 },
    { 0x82D4, 0x00, bb_00_82D4 },
    { 0x8141, 0x01, bb_01_8141 },
    { 0x8142, 0x01, bb_01_8142 },
    { 0x8145, 0x01, bb_01_8145 },
    { 0x8148, 0x01, bb_01_8148 },
    { 0x814E, 0x01, bb_01_814E },
    { 0x8151, 0x01, bb_01_8151 },
    { 0x8154, 0x01, bb_01_8154 },
    { 0x8159, 0x01, bb_01_8159 },
    { 0x815A, 0x01, bb_01_815A },
    { 0x815D, 0x01, bb_01_815D },
    { 0x8160, 0x01, bb_01_8160 },
    { 0x8166, 0x01, bb_01_8166 },
    { 0x8168, 0x01, bb_01_8168 },
    { 0x816E, 0x01, bb_01_816E },
    { 0x8173, 0x01, bb_01_8173 },
    { 0x8174, 0x01, bb_01_8174 },
    { 0x8179, 0x01, bb_01_8179 },
    { 0x817A, 0x01, bb_01_817A },
    { 0x817D, 0x01, bb_01_817D },
    { 0x8180, 0x01, bb_01_8180 },
    { 0x8183, 0x01, bb_01_8183 },
    { 0x8185, 0x01, bb_01_8185 },
    { 0x818A, 0x01, bb_01_818A },
    { 0x818D, 0x01, bb_01_818D },
    { 0x818E, 0x01, bb_01_818E },
    { 0x81A7, 0x01, bb_01_81A7 },
    { 0x81A9, 0x01, bb_01_81A9 },
    { 0x81AA, 0x01, bb_01_81AA },
    { 0x81AD, 0x01, bb_01_81AD },
    { 0x81B1, 0x01, bb_01_81B1 },
    { 0x81B2, 0x01, bb_01_81B2 },
    { 0x81B3, 0x01, bb_01_81B3 },
    { 0x81EA, 0x01, bb_01_81EA },
    { 0x81F0, 0x01, bb_01_81F0 },
    { 0x81F6, 0x01, bb_01_81F6 },
    { 0x81FC, 0x01, bb_01_81FC },
    { 0x8202, 0x01, bb_01_8202 },
    { 0x8203, 0x01, bb_01_8203 },
    { 0x8204, 0x01, bb_01_8204 },
    { 0x8205, 0x01, bb_01_8205 },
    { 0x8206, 0x01, bb_01_8206 },
    { 0x8209, 0x01, bb_01_8209 },
    { 0x820A, 0x01, bb_01_820A },
    { 0x820B, 0x01, bb_01_820B },
    { 0x820C, 0x01, bb_01_820C },
    { 0x820D, 0x01, bb_01_820D },
    { 0x820E, 0x01, bb_01_820E },
    { 0x8211, 0x01, bb_01_8211 },
    { 0x8212, 0x01, bb_01_8212 },
    { 0x8215, 0x01, bb_01_8215 },
    { 0x8219, 0x01, bb_01_8219 },
    { 0x821A, 0x01, bb_01_821A },
    { 0x821B, 0x01, bb_01_821B },
    { 0x821C, 0x01, bb_01_821C },
    { 0x821D, 0x01, bb_01_821D },
    { 0x821E, 0x01, bb_01_821E },
    { 0x821F, 0x01, bb_01_821F },
    { 0x8220, 0x01, bb_01_8220 },
    { 0x8221, 0x01, bb_01_8221 },
    { 0x8222, 0x01, bb_01_8222 },
    { 0x8223, 0x01, bb_01_8223 },
    { 0x8224, 0x01, bb_01_8224 },
    { 0x8225, 0x01, bb_01_8225 },
    { 0x8226, 0x01, bb_01_8226 },
    { 0x8227, 0x01, bb_01_8227 },
    { 0x8228, 0x01, bb_01_8228 },
    { 0x8229, 0x01, bb_01_8229 },
    { 0x822A, 0x01, bb_01_822A },
    { 0x822B, 0x01, bb_01_822B },
    { 0x822C, 0x01, bb_01_822C },
    { 0x822D, 0x01, bb_01_822D },
    { 0x822E, 0x01, bb_01_822E },
    { 0x822F, 0x01, bb_01_822F },
    { 0x8230, 0x01, bb_01_8230 },
    { 0x8231, 0x01, bb_01_8231 },
    { 0x8232, 0x01, bb_01_8232 },
    { 0x8233, 0x01, bb_01_8233 },
    { 0x8234, 0x01, bb_01_8234 },
    { 0x8235, 0x01, bb_01_8235 },
    { 0x8236, 0x01, bb_01_8236 },
    { 0x8237, 0x01, bb_01_8237 },
    { 0x8238, 0x01, bb_01_8238 },
    { 0x8239, 0x01, bb_01_8239 },
    { 0x823A, 0x01, bb_01_823A },
    { 0x823B, 0x01, bb_01_823B },
    { 0x823C, 0x01, bb_01_823C },
    { 0x823D, 0x01, bb_01_823D },
    { 0x823E, 0x01, bb_01_823E },
    { 0x823F, 0x01, bb_01_823F },
    { 0x8240, 0x01, bb_01_8240 },
    { 0x8241, 0x01, bb_01_8241 },
    { 0x8242, 0x01, bb_01_8242 },
    { 0x8243, 0x01, bb_01_8243 },
    { 0x8244, 0x01, bb_01_8244 },
    { 0x8245, 0x01, bb_01_8245 },
    { 0x8246, 0x01, bb_01_8246 },
    { 0x8247, 0x01, bb_01_8247 },
    { 0x8248, 0x01, bb_01_8248 },
    { 0x8249, 0x01, bb_01_8249 },
    { 0x824A, 0x01, bb_01_824A },
    { 0x824B, 0x01, bb_01_824B },
    { 0x824C, 0x01, bb_01_824C },
    { 0x824D, 0x01, bb_01_824D },
    { 0x824E, 0x01, bb_01_824E },
    { 0x824F, 0x01, bb_01_824F },
    { 0x8250, 0x01, bb_01_8250 },
    { 0x8251, 0x01, bb_01_8251 },
    { 0x8252, 0x01, bb_01_8252 },
    { 0x8253, 0x01, bb_01_8253 },
    { 0x8254, 0x01, bb_01_8254 },
    { 0x8255, 0x01, bb_01_8255 },
    { 0x8256, 0x01, bb_01_8256 },
    { 0x8257, 0x01, bb_01_8257 },
    { 0x8258, 0x01, bb_01_8258 },
    { 0x8259, 0x01, bb_01_8259 },
    { 0x825A, 0x01, bb_01_825A },
    { 0x825B, 0x01, bb_01_825B },
    { 0x825C, 0x01, bb_01_825C },
    { 0x825D, 0x01, bb_01_825D },
    { 0x825E, 0x01, bb_01_825E },
    { 0x825F, 0x01, bb_01_825F },
    { 0x8260, 0x01, bb_01_8260 },
    { 0x8261, 0x01, bb_01_8261 },
    { 0x8262, 0x01, bb_01_8262 },
    { 0x8263, 0x01, bb_01_8263 },
    { 0x8264, 0x01, bb_01_8264 },
    { 0x8266, 0x01, bb_01_8266 },
    { 0x8268, 0x01, bb_01_8268 },
    { 0x8269, 0x01, bb_01_8269 },
    { 0x826A, 0x01, bb_01_826A },
    { 0x826C, 0x01, bb_01_826C },
    { 0x826E, 0x01, bb_01_826E },
    { 0x826F, 0x01, bb_01_826F },
    { 0x8270, 0x01, bb_01_8270 },
    { 0x8272, 0x01, bb_01_8272 },
    { 0x8274, 0x01, bb_01_8274 },
    { 0x8277, 0x01, bb_01_8277 },
    { 0x827B, 0x01, bb_01_827B },
    { 0x827C, 0x01, bb_01_827C },
    { 0x827D, 0x01, bb_01_827D },
    { 0x827E, 0x01, bb_01_827E },
    { 0x827F, 0x01, bb_01_827F },
    { 0x8280, 0x01, bb_01_8280 },
    { 0x8281, 0x01, bb_01_8281 },
    { 0x8282, 0x01, bb_01_8282 },
    { 0x8283, 0x01, bb_01_8283 },
    { 0x8284, 0x01, bb_01_8284 },
    { 0x8285, 0x01, bb_01_8285 },
    { 0x8286, 0x01, bb_01_8286 },
    { 0x8287, 0x01, bb_01_8287 },
    { 0x8288, 0x01, bb_01_8288 },
    { 0x8289, 0x01, bb_01_8289 },
    { 0x828A, 0x01, bb_01_828A },
    { 0x828B, 0x01, bb_01_828B },
    { 0x828C, 0x01, bb_01_828C },
    { 0x828F, 0x01, bb_01_828F },
    { 0x8290, 0x01, bb_01_8290 },
    { 0x8291, 0x01, bb_01_8291 },
    { 0x8292, 0x01, bb_01_8292 },
    { 0x8293, 0x01, bb_01_8293 },
    { 0x8294, 0x01, bb_01_8294 },
    { 0x8295, 0x01, bb_01_8295 },
    { 0x8296, 0x01, bb_01_8296 },
    { 0x8298, 0x01, bb_01_8298 },
    { 0x829A, 0x01, bb_01_829A },
    { 0x829C, 0x01, bb_01_829C },
    { 0x829F, 0x01, bb_01_829F },
    { 0x82A0, 0x01, bb_01_82A0 },
    { 0x82A1, 0x01, bb_01_82A1 },
    { 0x82A2, 0x01, bb_01_82A2 },
    { 0x82A3, 0x01, bb_01_82A3 },
    { 0x82A4, 0x01, bb_01_82A4 },
    { 0x82A5, 0x01, bb_01_82A5 },
    { 0x82A6, 0x01, bb_01_82A6 },
    { 0x82A7, 0x01, bb_01_82A7 },
    { 0x82A8, 0x01, bb_01_82A8 },
    { 0x82AB, 0x01, bb_01_82AB },
    { 0x82B1, 0x01, bb_01_82B1 },
    { 0x82B3, 0x01, bb_01_82B3 },
    { 0x82B5, 0x01, bb_01_82B5 },
    { 0x82B6, 0x01, bb_01_82B6 },
    { 0x82B7, 0x01, bb_01_82B7 },
    { 0x82B8, 0x01, bb_01_82B8 },
    { 0x82B9, 0x01, bb_01_82B9 },
    { 0x82BA, 0x01, bb_01_82BA },
    { 0x82BB, 0x01, bb_01_82BB },
    { 0x82BC, 0x01, bb_01_82BC },
    { 0x82BD, 0x01, bb_01_82BD },
    { 0x82BE, 0x01, bb_01_82BE },
    { 0x82BF, 0x01, bb_01_82BF },
    { 0x82C0, 0x01, bb_01_82C0 },
    { 0x82C1, 0x01, bb_01_82C1 },
    { 0x82C2, 0x01, bb_01_82C2 },
    { 0x82C3, 0x01, bb_01_82C3 },
    { 0x82C4, 0x01, bb_01_82C4 },
    { 0x82C7, 0x01, bb_01_82C7 },
    { 0x82CA, 0x01, bb_01_82CA },
    { 0x81A2, 0x02, bb_02_81A2 },
    { 0x81A3, 0x02, bb_02_81A3 },
    { 0x81A4, 0x02, bb_02_81A4 },
    { 0x81A7, 0x02, bb_02_81A7 },
    { 0x81A8, 0x02, bb_02_81A8 },
    { 0x81A9, 0x02, bb_02_81A9 },
    { 0x81AB, 0x02, bb_02_81AB },
    { 0x81AC, 0x02, bb_02_81AC },
    { 0x81AF, 0x02, bb_02_81AF },
    { 0x81B0, 0x02, bb_02_81B0 },
    { 0x81B1, 0x02, bb_02_81B1 },
    { 0x81B2, 0x02, bb_02_81B2 },
    { 0x81B3, 0x02, bb_02_81B3 },
    { 0x81B4, 0x02, bb_02_81B4 },
    { 0x81B5, 0x02, bb_02_81B5 },
    { 0x81B6, 0x02, bb_02_81B6 },
    { 0x81B7, 0x02, bb_02_81B7 },
    { 0x81B8, 0x02, bb_02_81B8 },
    { 0x81B9, 0x02, bb_02_81B9 },
    { 0x81BB, 0x02, bb_02_81BB },
    { 0x81BC, 0x02, bb_02_81BC },
    { 0x81BE, 0x02, bb_02_81BE },
    { 0x81C1, 0x02, bb_02_81C1 },
    { 0x800C, 0x07, bb_07_800C },
    { 0x800D, 0x07, bb_07_800D },
    { 0x800E, 0x07, bb_07_800E },
    { 0x8010, 0x07, bb_07_8010 },
    { 0x82B7, 0x07, bb_07_82B7 },
    { 0x8319, 0x07, bb_07_8319 },
    { 0x831A, 0x07, bb_07_831A },
    { 0x8177, 0x0C, bb_0C_8177 },
    { 0x8179, 0x0C, bb_0C_8179 },
    { 0x817A, 0x0C, bb_0C_817A },
    { 0x8180, 0x0C, bb_0C_8180 },
    { 0x8182, 0x0C, bb_0C_8182 },
    { 0x8184, 0x0C, bb_0C_8184 },
    { 0x8186, 0x0C, bb_0C_8186 },
    { 0x818B, 0x0C, bb_0C_818B },
    { 0x818D, 0x0C, bb_0C_818D },
    { 0x818F, 0x0C, bb_0C_818F },
    { 0x8192, 0x0C, bb_0C_8192 },
    { 0x8194, 0x0C, bb_0C_8194 },
    { 0x8195, 0x0C, bb_0C_8195 },
    { 0x8196, 0x0C, bb_0C_8196 },
    { 0x8197, 0x0C, bb_0C_8197 },
    { 0x8198, 0x0C, bb_0C_8198 },
    { 0x81A2, 0x0C, bb_0C_81A2 },
    { 0x81A4, 0x0C, bb_0C_81A4 },
    { 0x81A5, 0x0C, bb_0C_81A5 },
    { 0x81A7, 0x0C, bb_0C_81A7 },
    { 0x81A8, 0x0C, bb_0C_81A8 },
    { 0x81AA, 0x0C, bb_0C_81AA },
    { 0x81AD, 0x0C, bb_0C_81AD },
    { 0x81AF, 0x0C, bb_0C_81AF },
    { 0x81B2, 0x0C, bb_0C_81B2 },
    { 0x81B5, 0x0C, bb_0C_81B5 },
    { 0x81B6, 0x0C, bb_0C_81B6 },
    { 0x81BF, 0x0C, bb_0C_81BF },
    { 0x81C1, 0x0C, bb_0C_81C1 },
    { 0x81C2, 0x0C, bb_0C_81C2 },
    { 0x81C3, 0x0C, bb_0C_81C3 },
    { 0xFFFF, 0xFF, NULL }
};

int sc_v11_static_step(SCV11Runtime* runtime) {
    if (!runtime || runtime->route_failed) return 0;

    uint16_t pc = runtime->machine.cpu.pc;
    uint16_t bank = runtime->machine.cpu.bank;

    for (size_t i = 0; dispatch_table[i].func; i++) {
        if (dispatch_table[i].pc == pc && dispatch_table[i].bank == bank) {
            dispatch_table[i].func(runtime);
            return 1;
        }
    }

    runtime->scheduler.cpu_instructions++;
    runtime->scheduler.master_clock += 6;
    runtime->machine.cpu.pc = (uint16_t)(pc + 1);
    return 1;
}