#ifndef OPCODE
#define OPCODE(name, code, mode)
#endif

// from http://www.emulator101.com/reference/6502-reference.html
// ADC
OPCODE(ADdwithCarry_I, 0x69, I)          // ADC #$NN Immediate $69 CZ- - - VN
OPCODE(ADdwithCarry_Ab, 0x6d, Ab)         // ADC $NNNN Absolute $6d CZ- - - VN
OPCODE(ADdwithCarry_AbX, 0x7d, AbX)        // ADC $NNNN,X Absolute,X $7d CZ- - - VN
OPCODE(ADdwithCarry_AbY, 0x79, AbY)        // ADC $NNNN,Y Absolute,Y $79 CZ- - - VN
OPCODE(ADdwithCarry_Z, 0x65, Z)          // ADC $NN Zero Page $65 CZ- - - VN
OPCODE(ADdwithCarry_ZX, 0x75, ZX)         // ADC $NN,X Zero Page,X $75 CZ- - - VN
OPCODE(ADdwithCarry_IndexIndir, 0x61, IndexIndir) // ADC ($NN,X) Indexed Indirect $61 CZ- - - VN
OPCODE(ADdwithCarry_IndirIndex, 0x71, IndirIndex) // ADC ($NN),Y Indirect Indexed $71 CZ- - - VN

// AND
OPCODE(AND_I, 0x29, I)          // AND #$NN Immediate $29 - Z- - - - N
OPCODE(AND_Ab, 0x2d, Ab)         // AND $NNNN Absolute $2d - Z- - - - N
OPCODE(AND_AbX, 0x3d, AbX)        // AND $NNNN,X Absolute,X $3d - Z- - - - N
OPCODE(AND_AbY, 0x39, AbY)        // AND $NNNN,Y Absolute,Y $39 - Z- - - - N
OPCODE(AND_Z, 0x25, Z)          // AND $NN Zero Page $25 - Z- - - - N
OPCODE(AND_ZX, 0x35, ZX)         // AND $NN,X Zero Page,X $35 - Z- - - - N
OPCODE(AND_IndexIndir, 0x21, IndexIndir) // AND ($NN,X) Indexed Indirect $21 - Z- - - - N
OPCODE(AND_IndirIndex, 0x31, IndirIndex) // AND ($NN),Y Indirect Indexed $31 - Z- - - - N

// ASL
OPCODE(ArithmeticShiftLeft_Acc, 0x0a, Acc)         // ASL A Accumulator $0a CZ- - - - N
OPCODE(ArithmeticShiftLeft_Ab, 0x0e, Ab)         // ASL $NNNN Absolute $0e CZ- - - - N
OPCODE(ArithmeticShiftLeft_AbX, 0x1e, AbX)        // ASL $NNNN,X Absolute,X $1e CZ- - - - N
OPCODE(ArithmeticShiftLeft_Z, 0x06, Z)          // ASL $NN Zero Page $06 CZ- - - - N
OPCODE(ArithmeticShiftLeft_ZX, 0x16, ZX)         // ASL $NN,X Zero Page,X $16 CZ- - - - N

OPCODE(BranchonCarryClear, 0x90, IMP)         // BCC $NN Relative $90 - - - - - - -
OPCODE(BranchonCarrySet, 0xb0, IMP)         // BCS $NN Relative $b0 - - - - - - -

OPCODE(BranchonEQual, 0xf0, IMP)         // BEQ $NN Relative $f0 - - - - - - -

OPCODE(BIT_Ab, 0x2c, Ab)         // BIT $NNNN Absolute $2c - Z- - - VN
OPCODE(BIT_Z, 0x24, Z)          // BIT $NN Zero Page $24 - Z- - - VN

OPCODE(BranchonMInus, 0x30, IMP)         // BMI $NN Relative $30 - - - - - - -

OPCODE(BranchonNotEqual, 0xd0, IMP)      // BNE $NN Relative $d0 - - - - - - -

OPCODE(BranchonPLus, 0x10, IMP)          // BPL $NN Relative $10 - - - - - - -

OPCODE(BReaK, 0x00, IMP)                 // BRK Implied $00 - - - - - - -

OPCODE(BranchonoVerflowClear, 0x50, IMP) // BVC $NN Relative $50 - - - - - - -

OPCODE(BranchonoVerflowSet, 0x70, IMP)   // BVS $NN Relative $70 - - - - - - -

OPCODE(CLearCarry, 0x18, IMP)            // CLC Implied $18 C- - - - - -
OPCODE(CLearDecimal, 0xd8, IMP)          // CLD Implied $d8 - - - D- - - Clear Decimal
OPCODE(CLearInterrupt, 0x58, IMP)        // CLI Implied $58 - - I- - - -
OPCODE(CLearoVerflow, 0xb8, IMP)         // CLV Implied $b8 - - - - - V-

OPCODE(CoMPareacc_I, 0xc9, I)          // CMP #$NN Immediate $c9 CZ- - - - N
OPCODE(CoMPareacc_Ab, 0xcd, Ab)         // CMP $NNNN Absolute $cd CZ- - - - N
OPCODE(CoMPareacc_AbX, 0xdd, AbX)        // CMP $NNNN,X Absolute,X $dd CZ- - - - N
OPCODE(CoMPareacc_AbY, 0xd9, AbY)        // CMP $NNNN,Y Absolute,Y $d9 CZ- - - - N
OPCODE(CoMPareacc_Z, 0xc5, Z)          // CMP $NN Zero Page $c5 CZ- - - - N
OPCODE(CoMPareacc_ZX, 0xd5, ZX)         // CMP $NN,X Zero Page,X $d5 CZ- - - - N
OPCODE(CoMPareacc_IndexIndir, 0xc1, IndexIndir) // CMP ($NN,X) Indexed Indirect $c1 CZ- - - - N
OPCODE(CoMPareacc_IndirIndex, 0xd1, IndirIndex) // CMP ($NN),Y Indirect Indexed $d1 CZ- - - - N

OPCODE(ComPareX_I, 0xe0, I)          // CPX #$NN Immediate $e0 CZ- - - - N
OPCODE(ComPareX_Ab, 0xec, Ab)         // CPX $NNNN Absolute $ec CZ- - - - N
OPCODE(ComPareX_Z, 0xe4, Z)          // CPX $NN Zero Page $e4 CZ- - - - N

OPCODE(ComPareY_I, 0xc0, I)          // CPY #$NN Immediate $c0 CZ- - - - N
OPCODE(ComPareY_Ab, 0xcc, Ab)         // CPY $NNNN Absolute $cc CZ- - - - N
OPCODE(ComPareY_Z, 0xc4, Z)          // CPY $NN Zero Page $c4 CZ- - - - N

OPCODE(DECrement_Ab, 0xce, Ab)         // DEC $NNNN Absolute $ce - Z- - - - N
OPCODE(DECrement_AbX, 0xde, AbX)        // DEC $NNNN,X Absolute,X $de - Z- - - - N
OPCODE(DECrement_Z, 0xc6, Z)          // DEC $NN Zero Page $c6 - Z- - - - N
OPCODE(DECrement_ZX, 0xd6, ZX)         // DEC $NN,X Zero Page,X $d6 - Z- - - - N

OPCODE(DEcrementX, 0xca, IMP)            // DEX Implied $ca - Z- - - - N
OPCODE(DEcrementY, 0x88, IMP)            // DEY Implied $88 - Z- - - - N

OPCODE(ExclusiveOR_I, 0x49, I)          // EOR #$NN Immediate $49 - Z- - - - N
OPCODE(ExclusiveOR_Ab, 0x4d, Ab)         // EOR $NNNN Absolute $4d - Z- - - - N
OPCODE(ExclusiveOR_AbX, 0x5d, AbX)        // EOR $NNNN,X Absolute,X $5d - Z- - - - N
OPCODE(ExclusiveOR_AbY, 0x59, AbY)        // EOR $NNNN,Y Absolute,Y $59 - Z- - - - N
OPCODE(ExclusiveOR_Z, 0x45, Z)          // EOR $NN Zero Page $45 - Z- - - - N
OPCODE(ExclusiveOR_ZX, 0x55, ZX)         // EOR $NN,X Zero Page,X $55 - Z- - - - N
OPCODE(ExclusiveOR_IndexIndir, 0x41, IndexIndir) // EOR ($NN,X) Indexed Indirect $41 - Z- - - - N
OPCODE(ExclusiveOR_IndirIndex, 0x51, IndirIndex) // EOR ($NN),Y Indirect Indexed $51 - Z- - - - N

OPCODE(INCrement_Ab, 0xee, Ab)         // INC $NNNN Absolute $ee - Z- - - - N
OPCODE(INCrement_AbX, 0xfe, AbX)        // INC $NNNN,X Absolute,X $fe - Z- - - - N
OPCODE(INCrement_Z, 0xe6, Z)          // INC $NN Zero Page $e6 - Z- - - - N
OPCODE(INCrement_ZX, 0xf6, ZX)         // INC $NN,X Zero Page,X $f6 - Z- - - - N

OPCODE(INcrementX, 0xe8, IMP)            // INX Implied $e8 - Z- - - - N
OPCODE(INcrementY, 0xc8, IMP)            // INY Implied $c8 - Z- - - - N

OPCODE(JuMP_Ab, 0x4c, Ab)             // JMP $NNNN Absolute $4c - - - - - - -
OPCODE(JuMP_Indir, 0x6c, IMP)          // JMP $NN Indirect $6c - - - - - - -

OPCODE(JumptoSubRoutine_Ab, 0x20, Ab) // JSR $NNNN Absolute $20 - - - - - - -

OPCODE(LoaDAcc_I, 0xa9, I)          // LDA #$NN Immediate $a9 - Z- - - - N
OPCODE(LoaDAcc_Ab, 0xad, Ab)         // LDA $NNNN Absolute $ad - Z- - - - N
OPCODE(LoaDAcc_AbX, 0xbd, AbX)        // LDA $NNNN,X Absolute,X $bd - Z- - - - N
OPCODE(LoaDAcc_AbY, 0xb9, AbY)        // LDA $NNNN,Y Absolute,Y $b9 - Z- - - - N
OPCODE(LoaDAcc_Z, 0xa5, Z)          // LDA $NN Zero Page $a5 - Z- - - - N
OPCODE(LoaDAcc_ZX, 0xb5, ZX)         // LDA $NN,X Zero Page,X $b5 - Z- - - - N
OPCODE(LoaDAcc_IndexIndir, 0xa1, IndexIndir) // LDA ($NN,X) Indexed Indirect $a1 - Z- - - - N
OPCODE(LoaDAcc_IndirIndex, 0xb1, IndirIndex) // LDA ($NN),Y Indirect Indexed $b1 - Z- - - - N

OPCODE(LoaDX_I, 0xa2, I)          // LDX #$NN Immediate $a2 - Z- - - - N
OPCODE(LoaDX_Ab, 0xae, Ab)         // LDX $NNNN Absolute $ae - Z- - - - N
OPCODE(LoaDX_AbY, 0xbe, AbY)        // LDX $NNNN,Y Absolute,Y $be - Z- - - - N
OPCODE(LoaDX_Z, 0xa6, Z)          // LDX $NN Zero Page $a6 - Z- - - - N
OPCODE(LoaDX_ZY, 0xb6, IMP)         // LDX $NN,Y Zero Page,Y $b6 - Z- - - - N

OPCODE(LoaDY_I, 0xa0, I)          // LDY #$NN Immediate $a0 - Z- - - - N
OPCODE(LoaDY_Ab, 0xac, Ab)         // LDY $NNNN Absolute $ac - Z- - - - N
OPCODE(LoaDY_AbX, 0xbc, AbX)        // LDY $NNNN,X Absolute,X $bc - Z- - - - N
OPCODE(LoaDY_Z, 0xa4, Z)          // LDY $NN Zero Page $a4 - Z- - - - N
OPCODE(LoaDY_ZX, 0xb4, ZX)         // LDY $NN,X Zero Page,X $b4 - Z- - - - N

OPCODE(LogicalShiftRight_Acc, 0x4a, IMP)        // LSR A Accumulator $4a CZ- - - - N
OPCODE(LogicalShiftRight_Ab, 0x4e, Ab)         // LSR $NNNN Absolute $4e CZ- - - - N
OPCODE(LogicalShiftRight_AbX, 0x5e, AbX)        // LSR $NNNN,X Absolute,X $5e CZ- - - - N
OPCODE(LogicalShiftRight_Z, 0x46, Z)          // LSR $NN Zero Page $46 CZ- - - - N
OPCODE(LogicalShiftRight_ZX, 0x56, ZX)         // LSR $NN,X Zero Page,X $56 CZ- - - - N

OPCODE(NoOPeration, 0xea, IMP)            // NOP Implied $ea - - - - - - -

OPCODE(ORwithAcc_I, 0x09, I)          // ORA #$NN Immediate $09 - Z- - - - N
OPCODE(ORwithAcc_Ab, 0x0d, Ab)         // ORA $NNNN Absolute $0d - Z- - - - N
OPCODE(ORwithAcc_AbX, 0x1d, AbX)        // ORA $NNNN,X Absolute,X $1d - Z- - - - N
OPCODE(ORwithAcc_AbY, 0x19, AbY)        // ORA $NNNN,Y Absolute,Y $19 - Z- - - - N
OPCODE(ORwithAcc_Z, 0x05, Z)          // ORA $NN Zero Page $05 - Z- - - - N
OPCODE(ORwithAcc_ZX, 0x15, ZX)         // ORA $NN,X Zero Page,X $15 - Z- - - - N
OPCODE(ORwithAcc_IndexIndir, 0x01, IndexIndir) // ORA ($NN,X) Indexed Indirect $01 - Z- - - - N
OPCODE(ORwithAcc_IndirIndex, 0x11, IndirIndex) // ORA ($NN),Y Indirect Indexed $11 - Z- - - - N

OPCODE(PusHAcc, 0x48, IMP)               // PHA Implied $48 - - - - - - -
OPCODE(PusHProcessorstatus, 0x08, IMP)   // PHP Implied $08 - - - - - - -
OPCODE(PuLlAcc, 0x68, IMP)               // PLA Implied $68 - Z- - - - N
OPCODE(PuLlProcessorstatus, 0x28, IMP)   // PLP Implied $28 CZIDBVN

OPCODE(ROtateLeft_Acc, 0x2a, IMP)        // ROL A Accumulator $2a CZ- - - - N
OPCODE(ROtateLeft_Ab, 0x2e, Ab)         // ROL $NNNN Absolute $2e CZ- - - - N
OPCODE(ROtateLeft_AbX, 0x3e, AbX)        // ROL $NNNN,X Absolute,X $3e CZ- - - - N
OPCODE(ROtateLeft_Z, 0x26, Z)          // ROL $NN Zero Page $26 CZ- - - - N
OPCODE(ROtateLeft_ZX, 0x36, ZX)         // ROL $NN,X Zero Page,X $36 CZ- - - - N

OPCODE(ROtateRight_Acc, 0x6a, IMP)        // ROR A Accumulator $6a CZ- - - - N
OPCODE(ROtateRight_Ab, 0x6e, Ab)         // ROR $NNNN Absolute $7e CZ- - - - N
OPCODE(ROtateRight_AbX, 0x7e, AbX)        // ROR $NNNN,X Absolute,X $6e CZ- - - - N
OPCODE(ROtateRight_Z, 0x66, Z)          // ROR $NN Zero Page $66 CZ- - - - N
OPCODE(ROtateRight_ZX, 0x76, ZX)         // ROR $NN,X Zero Page,X $76 CZ- - - - N

OPCODE(ReTurnfromInterrupt, 0x40, IMP)          // RTI Implied $40 - - - - - - -
OPCODE(ReTurnfromSubroutine, 0x60, IMP)         // RTS Implied $60 - - - - - - -

OPCODE(SuBtractwithCarry_I, 0xe9, I)          // SBC #$NN Immediate $e9 CZ- - - VN
OPCODE(SuBtractwithCarry_Ab, 0xed, Ab)         // SBC $NNNN Absolute $ed CZ- - - VN
OPCODE(SuBtractwithCarry_AbX, 0xfd, AbX)        // SBC $NNNN,X Absolute,X $fd CZ- - - VN
OPCODE(SuBtractwithCarry_AbY, 0xf9, AbY)        // SBC $NNNN,Y Absolute,Y $f9 CZ- - - VN
OPCODE(SuBtractwithCarry_Z, 0xe5, Z)          // SBC $NN Zero Page $e5 CZ- - - VN
OPCODE(SuBtractwithCarry_ZX, 0xf5, ZX)         // SBC $NN,X Zero Page,X $f5 CZ- - - VN
OPCODE(SuBtractwithCarry_IndexIndir, 0xe1, IndexIndir) // SBC ($NN,X) Indexed Indirect $e1 CZ- - - VN
OPCODE(SuBtractwithCarry_IndirIndex, 0xf1, IndirIndex) // SBC ($NN),Y Indirect Indexed $f1 CZ- - - VN

OPCODE(SEtCarry, 0x38, IMP)            // SEC Implied $38 C- - - - - -
OPCODE(SEtDecimal, 0xf8, IMP)          // SED Implied $f8 - - - D- - -
OPCODE(SEtInterrupt, 0x78, IMP)        // SEI Implied $78 - - I- - - -

OPCODE(SToreAcc_Ab, 0x8d, Ab)         // STA $NNNN Absolute $8d - - - - - - -
OPCODE(SToreAcc_AbX, 0x9d, AbX)        // STA $NNNN,X Absolute,X $9d - - - - - - -
OPCODE(SToreAcc_AbY, 0x99, AbY)        // STA $NNNN,Y Absolute,Y $99 - - - - - - -
OPCODE(SToreAcc_Z, 0x85, Z)          // STA $NN Zero Page $85 - - - - - - -
OPCODE(SToreAcc_ZX, 0x95, ZX)         // STA $NN,X Zero Page,X $95 - - - - - - -
OPCODE(SToreAcc_IndexIndir, 0x81, IndexIndir) // STA ($NN,X) Indexed Indirect $81 - - - - - - -
OPCODE(SToreAcc_IndirIndex, 0x91, IndirIndex) // STA ($NN),Y Indirect Indexed $91 - - - - - - -

OPCODE(SToreX_Ab, 0x8e, Ab)         // STX $NNNN Absolute $8e - - - - - - -
OPCODE(SToreX_Z, 0x86, Z)          // STX $NN Zero Page $86 - - - - - - -
OPCODE(SToreX_ZY, 0x96, IMP)         // STX $NN,Y Zero Page,Y $96 - - - - - - -

OPCODE(SToreY_Ab, 0x8c, Ab)         // STY $NNNN Absolute $8c - - - - - - -
OPCODE(SToreY_Z, 0x84, Z)          // STY $NN Zero Page $84 - - - - - - -
OPCODE(SToreY_ZX, 0x94, ZX)         // STY $NN,X Zero Page,X $94 - - - - - - -

OPCODE(TransferAtoX, 0xaa, IMP)            // TAX Implied $aa - Z- - - - N
OPCODE(TransferAtoY, 0xa8, IMP)            // TAY Implied $a8 - Z- - - - N
OPCODE(TransferStacktoX, 0xba, IMP)        // TSX Implied $ba - Z- - - - N
OPCODE(TransferXtoA, 0x8a, IMP)            // TXA Implied $8a - Z- - - - N
OPCODE(TransferXtoStack, 0x9a, IMP)        // TXS Implied $9a - - - - - - -
OPCODE(TransferYtoA, 0x98, IMP)            // TYA Implied $98 - Z- - - - N
#undef OPCODE