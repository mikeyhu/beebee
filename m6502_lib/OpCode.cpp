enum OpCode {
    // http://www.emulator101.com/reference/6502-reference.html

    // ADC
    ADdwithCarry_I = 0x69,           // ADC #$NN Immediate $69 CZ- - - VN
    ADdwithCarry_Ab = 0x6d,          // ADC $NNNN Absolute $6d CZ- - - VN
    ADdwithCarry_AbX = 0x7d,         // ADC $NNNN,X Absolute,X $7d CZ- - - VN
    ADdwithCarry_AbY = 0x79,         // ADC $NNNN,Y Absolute,Y $79 CZ- - - VN
    ADdwithCarry_Z = 0x65,           // ADC $NN Zero Page $65 CZ- - - VN
    ADdwithCarry_ZX = 0x75,          // ADC $NN,X Zero Page,X $75 CZ- - - VN
    ADdwithCarry_IndexIndir = 0x61,  // ADC ($NN,X) Indexed Indirect $61 CZ- - - VN
    ADdwithCarry_IndirIndex = 0x71,  // ADC ($NN),Y Indirect Indexed $71 CZ- - - VN

    // AND
    AND_I = 0x29,           // AND #$NN Immediate $29 - Z- - - - N
    AND_Ab = 0x2d,          // AND $NNNN Absolute $2d - Z- - - - N
    AND_AbX = 0x3d,         // AND $NNNN,X Absolute,X $3d - Z- - - - N
    AND_AbY = 0x39,         // AND $NNNN,Y Absolute,Y $39 - Z- - - - N
    AND_Z = 0x25,           // AND $NN Zero Page $25 - Z- - - - N
    AND_ZX = 0x35,          // AND $NN,X Zero Page,X $35 - Z- - - - N
    AND_IndexIndir = 0x21,  // AND ($NN,X) Indexed Indirect $21 - Z- - - - N
    AND_IndirIndex = 0x31,  // AND ($NN),Y Indirect Indexed $31 - Z- - - - N

    // ASL
    ArithmeticShiftLeft_Ac = 0x0a,          // ASL A Accumulator $0a CZ- - - - N
    ArithmeticShiftLeft_Ab = 0x0e,          // ASL $NNNN Absolute $0e CZ- - - - N
    ArithmeticShiftLeft_AbX = 0x1e,         // ASL $NNNN,X Absolute,X $1e CZ- - - - N
    ArithmeticShiftLeft_Z = 0x06,           // ASL $NN Zero Page $06 CZ- - - - N
    ArithmeticShiftLeft_ZX = 0x16,          // ASL $NN,X Zero Page,X $16 CZ- - - - N

    BranchonCarryClear = 0x90,          // BCC $NN Relative $90 - - - - - - -
    BranchonCarrySet = 0xb0,          // BCS $NN Relative $b0 - - - - - - -

    BranchonEQual = 0xf0,          // BEQ $NN Relative $f0 - - - - - - -

    BIT_Ab = 0x2c,          // BIT $NNNN Absolute $2c - Z- - - VN
    BIT_Z = 0x24,           // BIT $NN Zero Page $24 - Z- - - VN

    BranchonMInus = 0x30,          // BMI $NN Relative $30 - - - - - - -

    BranchonNotEqual = 0xd0,          // BNE $NN Relative $d0 - - - - - - -

    BranchonPLus = 0x10,          // BPL $NN Relative $10 - - - - - - -

    BReaK = 0x00,             // BRK Implied $00 - - - - - - -

    BranchonoVerflowClear = 0x50,          // BVC $NN Relative $50 - - - - - - -

    BranchonoVerflowSet = 0x70,          // BVS $NN Relative $70 - - - - - - -

    CLearCarry = 0x18,             // CLC Implied $18 C- - - - - -
    CLearDecimal = 0xd8,             // CLD Implied $d8 - - - D- - - Clear Decimal
    CLearInterrupt = 0x58,             // CLI Implied $58 - - I- - - -
    CLearoVerflow = 0xb8,             // CLV Implied $b8 - - - - - V-

    CoMPareacc_I = 0xc9,           // CMP #$NN Immediate $c9 CZ- - - - N
    CoMPareacc_Ab = 0xcd,          // CMP $NNNN Absolute $cd CZ- - - - N
    CoMPareacc_AbX = 0xdd,         // CMP $NNNN,X Absolute,X $dd CZ- - - - N
    CoMPareacc_AbY = 0xd9,         // CMP $NNNN,Y Absolute,Y $d9 CZ- - - - N
    CoMPareacc_Z = 0xc5,           // CMP $NN Zero Page $c5 CZ- - - - N
    CoMPareacc_ZX = 0xd5,          // CMP $NN,X Zero Page,X $d5 CZ- - - - N
    CoMPareacc_IndexIndir = 0xc1,  // CMP ($NN,X) Indexed Indirect $c1 CZ- - - - N
    CoMPareacc_IndirIndex = 0xd1,  // CMP ($NN),Y Indirect Indexed $d1 CZ- - - - N

    ComPareX_I = 0xe0,           // CPX #$NN Immediate $e0 CZ- - - - N
    ComPareX_Ab = 0xec,          // CPX $NNNN Absolute $ec CZ- - - - N
    ComPareX_Z = 0xe4,           // CPX $NN Zero Page $e4 CZ- - - - N

    ComPareY_I = 0xc0,           // CPY #$NN Immediate $c0 CZ- - - - N
    ComPareY_Ab = 0xcc,          // CPY $NNNN Absolute $cc CZ- - - - N
    ComPareY_Z = 0xc4,           // CPY $NN Zero Page $c4 CZ- - - - N

    DECrement_Ab = 0xce,          // DEC $NNNN Absolute $ce - Z- - - - N
    DECrement_AbX = 0xde,         // DEC $NNNN,X Absolute,X $de - Z- - - - N
    DECrement_Z = 0xc6,           // DEC $NN Zero Page $c6 - Z- - - - N
    DECrement_ZX = 0xd6,          // DEC $NN,X Zero Page,X $d6 - Z- - - - N

    DEcrementX = 0xca,             // DEX Implied $ca - Z- - - - N
    DEcrementY = 0x88,             // DEY Implied $88 - Z- - - - N

    ExclusiveOR_I = 0x49,           // EOR #$NN Immediate $49 - Z- - - - N
    ExclusiveOR_Ab = 0x4d,          // EOR $NNNN Absolute $4d - Z- - - - N
    ExclusiveOR_AbX = 0x5d,         // EOR $NNNN,X Absolute,X $5d - Z- - - - N
    ExclusiveOR_AbY = 0x59,         // EOR $NNNN,Y Absolute,Y $59 - Z- - - - N
    ExclusiveOR_Z = 0x45,           // EOR $NN Zero Page $45 - Z- - - - N
    ExclusiveOR_ZX = 0x55,          // EOR $NN,X Zero Page,X $55 - Z- - - - N
    ExclusiveOR_IndexIndir = 0x41,  // EOR ($NN,X) Indexed Indirect $41 - Z- - - - N
    ExclusiveOR_IndirIndex = 0x51,  // EOR ($NN),Y Indirect Indexed $51 - Z- - - - N

    INCrement_Ab = 0xee,          // INC $NNNN Absolute $ee - Z- - - - N
    INCrement_AbX = 0xfe,         // INC $NNNN,X Absolute,X $fe - Z- - - - N
    INCrement_Z = 0xe6,           // INC $NN Zero Page $e6 - Z- - - - N
    INCrement_ZX = 0xf6,          // INC $NN,X Zero Page,X $f6 - Z- - - - N

    INcrementX = 0xe8,             // INX Implied $e8 - Z- - - - N
    INcrementY = 0xc8,             // INY Implied $c8 - Z- - - - N

    JuMP_Ab = 0x4c,          // JMP $NNNN Absolute $4c - - - - - - -
    JuMP_Indir = 0x6c,           // JMP $NN Indirect $6c - - - - - - -

    JumptoSubRoutine_Ab = 0x20,          // JSR $NNNN Absolute $20 - - - - - - -

    LoaDAcc_I = 0xa9,           // LDA #$NN Immediate $a9 - Z- - - - N
    LoaDAcc_Ab = 0xad,          // LDA $NNNN Absolute $ad - Z- - - - N
    LoaDAcc_AbX = 0xbd,         // LDA $NNNN,X Absolute,X $bd - Z- - - - N
    LoaDAcc_AbY = 0xb9,         // LDA $NNNN,Y Absolute,Y $b9 - Z- - - - N
    LoaDAcc_Z = 0xa5,           // LDA $NN Zero Page $a5 - Z- - - - N
    LoaDAcc_ZX = 0xb5,          // LDA $NN,X Zero Page,X $b5 - Z- - - - N
    LoaDAcc_IndexIndir = 0xa1,  // LDA ($NN,X) Indexed Indirect $a1 - Z- - - - N
    LoaDAcc_IndirIndex = 0xb1,  // LDA ($NN),Y Indirect Indexed $b1 - Z- - - - N

    LoaDX_I = 0xa2,           // LDX #$NN Immediate $a2 - Z- - - - N
    LoaDX_Ab = 0xae,          // LDX $NNNN Absolute $ae - Z- - - - N
    LoaDX_AbY = 0xbe,         // LDX $NNNN,Y Absolute,Y $be - Z- - - - N
    LoaDX_Z = 0xa6,           // LDX $NN Zero Page $a6 - Z- - - - N
    LoaDX_ZY = 0xb6,          // LDX $NN,Y Zero Page,Y $b6 - Z- - - - N

    LoaDY_I = 0xa0,           // LDY #$NN Immediate $a0 - Z- - - - N
    LoaDY_Ab = 0xac,          // LDY $NNNN Absolute $ac - Z- - - - N
    LoaDY_AbX = 0xbc,         // LDY $NNNN,X Absolute,X $bc - Z- - - - N
    LoaDY_Z = 0xa4,           // LDY $NN Zero Page $a4 - Z- - - - N
    LoaDY_ZX = 0xb4,          // LDY $NN,X Zero Page,X $b4 - Z- - - - N

    LogicalShiftRight_Acc = 0x4a,         // LSR A Accumulator $4a CZ- - - - N
    LogicalShiftRight_Ab = 0x4e,          // LSR $NNNN Absolute $4e CZ- - - - N
    LogicalShiftRight_AbX = 0x5e,         // LSR $NNNN,X Absolute,X $5e CZ- - - - N
    LogicalShiftRight_Z = 0x46,           // LSR $NN Zero Page $46 CZ- - - - N
    LogicalShiftRight_ZX = 0x56,          // LSR $NN,X Zero Page,X $56 CZ- - - - N

    NoOPeration = 0xea,             // NOP Implied $ea - - - - - - -

    ORwithAcc_I = 0x09,           // ORA #$NN Immediate $09 - Z- - - - N
    ORwithAcc_Ab = 0x0d,          // ORA $NNNN Absolute $0d - Z- - - - N
    ORwithAcc_AbX = 0x1d,         // ORA $NNNN,X Absolute,X $1d - Z- - - - N
    ORwithAcc_AbY = 0x19,         // ORA $NNNN,Y Absolute,Y $19 - Z- - - - N
    ORwithAcc_Z = 0x05,           // ORA $NN Zero Page $05 - Z- - - - N
    ORwithAcc_ZX = 0x15,          // ORA $NN,X Zero Page,X $15 - Z- - - - N
    ORwithAcc_IndexIndir = 0x01,  // ORA ($NN,X) Indexed Indirect $01 - Z- - - - N
    ORwithAcc_IndirIndex = 0x11,  // ORA ($NN),Y Indirect Indexed $11 - Z- - - - N

    PusHAcc = 0x48,             // PHA Implied $48 - - - - - - -
    PusHProcessorstatus = 0x08,             // PHP Implied $08 - - - - - - -
    PuLlAcc = 0x68,             // PLA Implied $68 - Z- - - - N
    PuLlProcessorstatus = 0x28,             // PLP Implied $28 CZIDBVN

    ROtateLeft_Acc = 0x2a,         // ROL A Accumulator $2a CZ- - - - N
    ROtateLeft_Ab = 0x2e,          // ROL $NNNN Absolute $2e CZ- - - - N
    ROtateLeft_AbX = 0x3e,         // ROL $NNNN,X Absolute,X $3e CZ- - - - N
    ROtateLeft_Z = 0x26,           // ROL $NN Zero Page $26 CZ- - - - N
    ROtateLeft_ZX = 0x36,          // ROL $NN,X Zero Page,X $36 CZ- - - - N

    ROtateRight_Acc = 0x6a,         // ROR A Accumulator $6a CZ- - - - N
    ROtateRight_Ab = 0x6e,          // ROR $NNNN Absolute $7e CZ- - - - N
    ROtateRight_AbX = 0x7e,         // ROR $NNNN,X Absolute,X $6e CZ- - - - N
    ROtateRight_Z = 0x66,           // ROR $NN Zero Page $66 CZ- - - - N
    ROtateRight_ZX = 0x76,          // ROR $NN,X Zero Page,X $76 CZ- - - - N

    ReTurnfromInterrupt = 0x40,             // RTI Implied $40 - - - - - - -
    ReTurnfromSubroutine = 0x60,             // RTS Implied $60 - - - - - - -

    SuBtractwithCarry_I = 0xe9,           // SBC #$NN Immediate $e9 CZ- - - VN
    SuBtractwithCarry_Ab = 0xed,          // SBC $NNNN Absolute $ed CZ- - - VN
    SuBtractwithCarry_AbX = 0xfd,         // SBC $NNNN,X Absolute,X $fd CZ- - - VN
    SuBtractwithCarry_AbY = 0xf9,         // SBC $NNNN,Y Absolute,Y $f9 CZ- - - VN
    SuBtractwithCarry_Z = 0xe5,           // SBC $NN Zero Page $e5 CZ- - - VN
    SuBtractwithCarry_ZX = 0xf5,          // SBC $NN,X Zero Page,X $f5 CZ- - - VN
    SuBtractwithCarry_IndexIndir = 0xe1,  // SBC ($NN,X) Indexed Indirect $e1 CZ- - - VN
    SuBtractwithCarry_IndirIndex = 0xf1,  // SBC ($NN),Y Indirect Indexed $f1 CZ- - - VN

    SEtCarry = 0x38,           // SEC Implied $38 C- - - - - -
    SEtDecimal = 0xf8,           // SED Implied $f8 - - - D- - -
    SEtInterrupt = 0x78,           // SEI Implied $78 - - I- - - -

    SToreAcc_Ab = 0x8d,          // STA $NNNN Absolute $8d - - - - - - -
    SToreAcc_AbX = 0x9d,         // STA $NNNN,X Absolute,X $9d - - - - - - -
    SToreAcc_AbY = 0x99,         // STA $NNNN,Y Absolute,Y $99 - - - - - - -
    SToreAcc_Z = 0x85,           // STA $NN Zero Page $85 - - - - - - -
    SToreAcc_ZX = 0x95,          // STA $NN,X Zero Page,X $95 - - - - - - -
    SToreAcc_IndexIndir = 0x81,  // STA ($NN,X) Indexed Indirect $81 - - - - - - -
    SToreAcc_IndirIndex = 0x91,  // STA ($NN),Y Indirect Indexed $91 - - - - - - -

    SToreX_Ab = 0x8e,          // STX $NNNN Absolute $8e - - - - - - -
    SToreX_Z = 0x86,           // STX $NN Zero Page $86 - - - - - - -
    SToreX_ZY = 0x96,          // STX $NN,Y Zero Page,Y $96 - - - - - - -

    SToreY_Ab = 0x8c,          // STY $NNNN Absolute $8c - - - - - - -
    SToreY_Z = 0x84,           // STY $NN Zero Page $84 - - - - - - -
    SToreY_ZX = 0x94,          // STY $NN,X Zero Page,X $94 - - - - - - -

    TransferAtoX = 0xaa,             // TAX Implied $aa - Z- - - - N
    TransferAtoY = 0xa8,             // TAY Implied $a8 - Z- - - - N
    TransferStacktoX = 0xba,             // TSX Implied $ba - Z- - - - N
    TransferXtoA = 0x8a,             // TXA Implied $8a - Z- - - - N
    TransferXtoStack = 0x9a,             // TXS Implied $9a - - - - - - -
    TransferYtoA = 0x98              // TYA Implied $98 - Z- - - - N
};