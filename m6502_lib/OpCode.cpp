enum OpCode {
    // http://www.emulator101.com/reference/6502-reference.html

    ADC_I = 0x69,           // ADC #$NN Immediate $69 CZ- - - VN
    ADC_Ab = 0x6d,          // ADC $NNNN Absolute $6d CZ- - - VN
    ADC_AbX = 0x7d,         // ADC $NNNN,X Absolute,X $7d CZ- - - VN
    ADC_AbY = 0x79,         // ADC $NNNN,Y Absolute,Y $79 CZ- - - VN
    ADC_Z = 0x65,           // ADC $NN Zero Page $65 CZ- - - VN
    ADC_ZX = 0x75,          // ADC $NN,X Zero Page,X $75 CZ- - - VN
    ADC_IndexIndir = 0x61,  // ADC ($NN,X) Indexed Indirect $61 CZ- - - VN
    ADC_IndirIndex = 0x71,  // ADC ($NN),Y Indirect Indexed $71 CZ- - - VN


    AND_I = 0x29,           // AND #$NN Immediate $29 - Z- - - - N
    AND_Ab = 0x2d,          // AND $NNNN Absolute $2d - Z- - - - N
    AND_AbX = 0x3d,         // AND $NNNN,X Absolute,X $3d - Z- - - - N
    AND_AbY = 0x39,         // AND $NNNN,Y Absolute,Y $39 - Z- - - - N
    AND_Z = 0x25,           // AND $NN Zero Page $25 - Z- - - - N
    AND_ZX = 0x35,          // AND $NN,X Zero Page,X $35 - Z- - - - N
    AND_IndexIndir = 0x21,  // AND ($NN,X) Indexed Indirect $21 - Z- - - - N
    AND_IndirIndex = 0x31,  // AND ($NN),Y Indirect Indexed $31 - Z- - - - N

    ASL_Ac = 0x0a,          // ASL A Accumulator $0a CZ- - - - N
    ASL_Ab = 0x0e,          // ASL $NNNN Absolute $0e CZ- - - - N
    ASL_AbX = 0x1e,         // ASL $NNNN,X Absolute,X $1e CZ- - - - N
    ASL_Z = 0x06,           // ASL $NN Zero Page $06 CZ- - - - N
    ASL_ZX = 0x16,          // ASL $NN,X Zero Page,X $16 CZ- - - - N

    BCC_Re = 0x90,          // BCC $NN Relative $90 - - - - - - -

    BCS_Re = 0xb0,          // BCS $NN Relative $b0 - - - - - - -

    BEQ_Re = 0xf0,          // BEQ $NN Relative $f0 - - - - - - -

    BIT_Ab = 0x2c,          // BIT $NNNN Absolute $2c - Z- - - VN
    BIT_Z = 0x24,           // BIT $NN Zero Page $24 - Z- - - VN

    BMI_Re = 0x30,          // BMI $NN Relative $30 - - - - - - -

    BNE_Re = 0xd0,          // BNE $NN Relative $d0 - - - - - - -

    BPL_Re = 0x10,          // BPL $NN Relative $10 - - - - - - -

    BRK = 0x00,             // BRK Implied $00 - - - - - - -

    BVC_Re = 0x50,          // BVC $NN Relative $50 - - - - - - -

    BVS_Re = 0x70,          // BVS $NN Relative $70 - - - - - - -

    CLC = 0x18,             // CLC Implied $18 C- - - - - -
    CLD = 0xd8,             // CLD Implied $d8 - - - D- - - Clear Decimal
    CLI = 0x58,             // CLI Implied $58 - - I- - - -
    CLV = 0xb8,             // CLV Implied $b8 - - - - - V-

    CMP_I = 0xc9,           // CMP #$NN Immediate $c9 CZ- - - - N
    CMP_Ab = 0xcd,          // CMP $NNNN Absolute $cd CZ- - - - N
    CMP_AbX = 0xdd,         // CMP $NNNN,X Absolute,X $dd CZ- - - - N
    CMP_AbY = 0xd9,         // CMP $NNNN,Y Absolute,Y $d9 CZ- - - - N
    CMP_Z = 0xc5,           // CMP $NN Zero Page $c5 CZ- - - - N
    CMP_ZX = 0xd5,          // CMP $NN,X Zero Page,X $d5 CZ- - - - N
    CMP_IndexIndir = 0xc1,  // CMP ($NN,X) Indexed Indirect $c1 CZ- - - - N
    CMP_IndirIndex = 0xd1,  // CMP ($NN),Y Indirect Indexed $d1 CZ- - - - N

    CPX_I = 0xe0,           // CPX #$NN Immediate $e0 CZ- - - - N
    CPX_Ab = 0xec,          // CPX $NNNN Absolute $ec CZ- - - - N
    CPX_Z = 0xe4,           // CPX $NN Zero Page $e4 CZ- - - - N

    CPY_I = 0xc0,           // CPY #$NN Immediate $c0 CZ- - - - N
    CPY_Ab = 0xcc,          // CPY $NNNN Absolute $cc CZ- - - - N
    CPY_Z = 0xc4,           // CPY $NN Zero Page $c4 CZ- - - - N

    DEC_Ab = 0xce,          // DEC $NNNN Absolute $ce - Z- - - - N
    DEC_AbX = 0xde,         // DEC $NNNN,X Absolute,X $de - Z- - - - N
    DEC_Z = 0xc6,           // DEC $NN Zero Page $c6 - Z- - - - N
    DEC_ZX = 0xd6,          // DEC $NN,X Zero Page,X $d6 - Z- - - - N

    DEX = 0xca,             // DEX Implied $ca - Z- - - - N
    DEY = 0x88,             // DEY Implied $88 - Z- - - - N

    EOR_I = 0x49,           // EOR #$NN Immediate $49 - Z- - - - N
    EOR_Ab = 0x4d,          // EOR $NNNN Absolute $4d - Z- - - - N
    EOR_AbX = 0x5d,         // EOR $NNNN,X Absolute,X $5d - Z- - - - N
    EOR_AbY = 0x59,         // EOR $NNNN,Y Absolute,Y $59 - Z- - - - N
    EOR_Z = 0x45,           // EOR $NN Zero Page $45 - Z- - - - N
    EOR_ZX = 0x55,          // EOR $NN,X Zero Page,X $55 - Z- - - - N
    EOR_IndexIndir = 0x41,  // EOR ($NN,X) Indexed Indirect $41 - Z- - - - N
    EOR_IndirIndex = 0x51,  // EOR ($NN),Y Indirect Indexed $51 - Z- - - - N

    INC_Ab = 0xee,          // INC $NNNN Absolute $ee - Z- - - - N
    INC_AbX = 0xfe,         // INC $NNNN,X Absolute,X $fe - Z- - - - N
    INC_Z = 0xe6,           // INC $NN Zero Page $e6 - Z- - - - N
    INC_ZX = 0xf6,          // INC $NN,X Zero Page,X $f6 - Z- - - - N

    INX = 0xe8,             // INX Implied $e8 - Z- - - - N
    INY = 0xc8,             // INY Implied $c8 - Z- - - - N

    JMP_Ab = 0x4c,          // JMP $NNNN Absolute $4c - - - - - - -
    JMP_Indir = 0x6c,           // JMP $NN Indirect $6c - - - - - - -

    JSR_Ab = 0x20,          // JSR $NNNN Absolute $20 - - - - - - -

    LDA_I = 0xa9,           // LDA #$NN Immediate $a9 - Z- - - - N
    LDA_Ab = 0xad,          // LDA $NNNN Absolute $ad - Z- - - - N
    LDA_AbX = 0xbd,         // LDA $NNNN,X Absolute,X $bd - Z- - - - N
    LDA_AbY = 0xb9,         // LDA $NNNN,Y Absolute,Y $b9 - Z- - - - N
    LDA_Z = 0xa5,           // LDA $NN Zero Page $a5 - Z- - - - N
    LDA_ZX = 0xb5,          // LDA $NN,X Zero Page,X $b5 - Z- - - - N
    LDA_IndexIndir = 0xa1,  // LDA ($NN,X) Indexed Indirect $a1 - Z- - - - N
    LDA_IndirIndex = 0xb1,  // LDA ($NN),Y Indirect Indexed $b1 - Z- - - - N

    LDX_I = 0xa2,           // LDX #$NN Immediate $a2 - Z- - - - N
    LDX_Ab = 0xae,          // LDX $NNNN Absolute $ae - Z- - - - N
    LDX_AbY = 0xbe,         // LDX $NNNN,Y Absolute,Y $be - Z- - - - N
    LDX_Z = 0xa6,           // LDX $NN Zero Page $a6 - Z- - - - N
    LDX_ZX = 0xb6,          // LDX $NN,Y Zero Page,Y $b6 - Z- - - - N

    LDY_I = 0xa0,           // LDY #$NN Immediate $a0 - Z- - - - N
    LDY_Ab = 0xac,          // LDY $NNNN Absolute $ac - Z- - - - N
    LDY_AbX = 0xbc,         // LDY $NNNN,X Absolute,X $bc - Z- - - - N
    LDY_Z = 0xa4,           // LDY $NN Zero Page $a4 - Z- - - - N
    LDY_ZX = 0xb4,          // LDY $NN,X Zero Page,X $b4 - Z- - - - N

    LSR_Acc = 0x4a,         // LSR A Accumulator $4a CZ- - - - N
    LSR_Ab = 0x4e,          // LSR $NNNN Absolute $4e CZ- - - - N
    LSR_AbX = 0x5e,         // LSR $NNNN,X Absolute,X $5e CZ- - - - N
    LSR_Z = 0x46,           // LSR $NN Zero Page $46 CZ- - - - N
    LSR_ZX = 0x56,          // LSR $NN,X Zero Page,X $56 CZ- - - - N

    NOP = 0xea,             // NOP Implied $ea - - - - - - -

    ORA_I = 0x09,           // ORA #$NN Immediate $09 - Z- - - - N
    ORA_Ab = 0x0d,          // ORA $NNNN Absolute $0d - Z- - - - N
    ORA_AbX = 0x1d,         // ORA $NNNN,X Absolute,X $1d - Z- - - - N
    ORA_AbY = 0x19,         // ORA $NNNN,Y Absolute,Y $19 - Z- - - - N
    ORA_Z = 0x05,           // ORA $NN Zero Page $05 - Z- - - - N
    ORA_ZX = 0x15,          // ORA $NN,X Zero Page,X $15 - Z- - - - N
    ORA_IndexIndir = 0x01,  // ORA ($NN,X) Indexed Indirect $01 - Z- - - - N
    ORA_IndirIndex = 0x11,  // ORA ($NN),Y Indirect Indexed $11 - Z- - - - N

    PHA = 0x48,             // PHA Implied $48 - - - - - - -
    PHP = 0x08,             // PHP Implied $08 - - - - - - -
    PLA = 0x68,             // PLA Implied $68 - Z- - - - N
    PLP = 0x28,             // PLP Implied $28 CZIDBVN

    ROL_Acc = 0x2a,         // ROL A Accumulator $2a CZ- - - - N
    ROL_Ab = 0x2e,          // ROL $NNNN Absolute $2e CZ- - - - N
    ROL_AbX = 0x3e,         // ROL $NNNN,X Absolute,X $3e CZ- - - - N
    ROL_Z = 0x26,           // ROL $NN Zero Page $26 CZ- - - - N
    ROL_ZX = 0x36,          // ROL $NN,X Zero Page,X $36 CZ- - - - N

    ROR_Acc = 0x6a,         // ROR A Accumulator $6a CZ- - - - N
    ROR_Ab = 0x7e,          // ROR $NNNN Absolute $7e CZ- - - - N
    ROR_AbX = 0x6e,         // ROR $NNNN,X Absolute,X $6e CZ- - - - N
    ROR_Z = 0x66,           // ROR $NN Zero Page $66 CZ- - - - N
    ROR_ZX = 0x76,          // ROR $NN,X Zero Page,X $76 CZ- - - - N

    RTI = 0x40,             // RTI Implied $40 - - - - - - -
    RTS = 0x60,             // RTS Implied $60 - - - - - - -

    SBC_I = 0xe9,           // SBC #$NN Immediate $e9 CZ- - - VN
    SBC_Ab = 0xed,          // SBC $NNNN Absolute $ed CZ- - - VN
    SBC_AbX = 0xfd,         // SBC $NNNN,X Absolute,X $fd CZ- - - VN
    SBC_AbY = 0xf9,         // SBC $NNNN,Y Absolute,Y $f9 CZ- - - VN
    SBC_Z = 0xe5,           // SBC $NN Zero Page $e5 CZ- - - VN
    SBC_ZX = 0xf5,          // SBC $NN,X Zero Page,X $f5 CZ- - - VN
    SBC_IndexIndir = 0xe1,  // SBC ($NN,X) Indexed Indirect $e1 CZ- - - VN
    SBC_IndirIndex = 0xf1,  // SBC ($NN),Y Indirect Indexed $f1 CZ- - - VN

    SEC_I = 0x38,           // SEC Implied $38 C- - - - - -
    SED_I = 0xf8,           // SED Implied $f8 - - - D- - -
    SEI_I = 0x78,           // SEI Implied $78 - - I- - - -

    STA_Ab = 0x8d,          // STA $NNNN Absolute $8d - - - - - - -
    STA_AbX = 0x9d,         // STA $NNNN,X Absolute,X $9d - - - - - - -
    STA_AbY = 0x99,         // STA $NNNN,Y Absolute,Y $99 - - - - - - -
    STA_Z = 0x85,           // STA $NN Zero Page $85 - - - - - - -
    STA_ZX = 0x95,          // STA $NN,X Zero Page,X $95 - - - - - - -
    STA_IndexIndir = 0x81,  // STA ($NN,X) Indexed Indirect $81 - - - - - - -
    STA_IndirIndex = 0x91,  // STA ($NN),Y Indirect Indexed $91 - - - - - - -

    STX_Ab = 0x8e,          // STX $NNNN Absolute $8e - - - - - - -
    STX_Z = 0x86,           // STX $NN Zero Page $86 - - - - - - -
    STX_ZY = 0x96,          // STX $NN,Y Zero Page,Y $96 - - - - - - -

    STY_Ab = 0x8c,          // STY $NNNN Absolute $8c - - - - - - -
    STY_Z = 0x84,           // STY $NN Zero Page $84 - - - - - - -
    STY_ZX = 0x94,          // STY $NN,X Zero Page,X $94 - - - - - - -

    TAX = 0xaa,             // TAX Implied $aa - Z- - - - N
    TAY = 0xa8,             // TAY Implied $a8 - Z- - - - N
    TSX = 0xba,             // TSX Implied $ba - Z- - - - N
    TXA = 0x8a,             // TXA Implied $8a - Z- - - - N
    TXS = 0x9a,             // TXS Implied $9a - - - - - - -
    TYA = 0x98              // TYA Implied $98 - Z- - - - N
};