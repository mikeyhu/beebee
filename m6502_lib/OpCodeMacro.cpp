#ifndef OPCODE
#define OPCODE(name, code, function, mode)
#endif

// from http://www.emulator101.com/reference/6502-reference.html
// ADC
OPCODE(ADdwithCarry_I, 0x69, opAddWithCarry, I)          // ADC #$NN Immediate $69 CZ- - - VN
OPCODE(ADdwithCarry_Ab, 0x6d, opAddWithCarry, Ab)         // ADC $NNNN Absolute $6d CZ- - - VN
OPCODE(ADdwithCarry_AbX, 0x7d, opAddWithCarry, AbX)        // ADC $NNNN,X Absolute,X $7d CZ- - - VN
OPCODE(ADdwithCarry_AbY, 0x79, opAddWithCarry, AbY)        // ADC $NNNN,Y Absolute,Y $79 CZ- - - VN
OPCODE(ADdwithCarry_Z, 0x65, opAddWithCarry, Z)          // ADC $NN Zero Page $65 CZ- - - VN
OPCODE(ADdwithCarry_ZX, 0x75, opAddWithCarry, ZX)         // ADC $NN,X Zero Page,X $75 CZ- - - VN
OPCODE(ADdwithCarry_IndexIndir, 0x61, opAddWithCarry, IndexIndir) // ADC ($NN,X) Indexed Indirect $61 CZ- - - VN
OPCODE(ADdwithCarry_IndirIndex, 0x71, opAddWithCarry, IndirIndex) // ADC ($NN),Y Indirect Indexed $71 CZ- - - VN

// AND
OPCODE(AND_I, 0x29, opAnd, I)          // AND #$NN Immediate $29 - Z- - - - N
OPCODE(AND_Ab, 0x2d, opAnd, Ab)         // AND $NNNN Absolute $2d - Z- - - - N
OPCODE(AND_AbX, 0x3d, opAnd, AbX)        // AND $NNNN,X Absolute,X $3d - Z- - - - N
OPCODE(AND_AbY, 0x39, opAnd, AbY)        // AND $NNNN,Y Absolute,Y $39 - Z- - - - N
OPCODE(AND_Z, 0x25, opAnd, Z)          // AND $NN Zero Page $25 - Z- - - - N
OPCODE(AND_ZX, 0x35, opAnd, ZX)         // AND $NN,X Zero Page,X $35 - Z- - - - N
OPCODE(AND_IndexIndir, 0x21, opAnd, IndexIndir) // AND ($NN,X) Indexed Indirect $21 - Z- - - - N
OPCODE(AND_IndirIndex, 0x31, opAnd, IndirIndex) // AND ($NN),Y Indirect Indexed $31 - Z- - - - N

// ASL
OPCODE(ArithmeticShiftLeft_Acc, 0x0a, opArithmeticShiftLeft, Acc)         // ASL A Accumulator $0a CZ- - - - N
OPCODE(ArithmeticShiftLeft_Ab, 0x0e, opArithmeticShiftLeft, Ab)         // ASL $NNNN Absolute $0e CZ- - - - N
OPCODE(ArithmeticShiftLeft_AbX, 0x1e, opArithmeticShiftLeft, AbX)        // ASL $NNNN,X Absolute,X $1e CZ- - - - N
OPCODE(ArithmeticShiftLeft_Z, 0x06, opArithmeticShiftLeft, Z)          // ASL $NN Zero Page $06 CZ- - - - N
OPCODE(ArithmeticShiftLeft_ZX, 0x16, opArithmeticShiftLeft, ZX)         // ASL $NN,X Zero Page,X $16 CZ- - - - N

OPCODE(BranchonCarryClear, 0x90, opBranchonCarryClear, IMP)         // BCC $NN Relative $90 - - - - - - -
OPCODE(BranchonCarrySet, 0xb0, opBranchonCarrySet, IMP)         // BCS $NN Relative $b0 - - - - - - -

OPCODE(BranchonEQual, 0xf0, opBranchonEqual, IMP)         // BEQ $NN Relative $f0 - - - - - - -

OPCODE(BIT_Ab, 0x2c, opBit, Ab)         // BIT $NNNN Absolute $2c - Z- - - VN
OPCODE(BIT_Z, 0x24, opBit, Z)          // BIT $NN Zero Page $24 - Z- - - VN

OPCODE(BranchonMInus, 0x30, opBranchOnMinus, IMP)         // BMI $NN Relative $30 - - - - - - -

OPCODE(BranchonNotEqual, 0xd0, opBranchOnNotEqual, IMP)      // BNE $NN Relative $d0 - - - - - - -

OPCODE(BranchonPLus, 0x10, opBranchOnPlus, IMP)          // BPL $NN Relative $10 - - - - - - -

OPCODE(BReaK, 0x00, opBreak, IMP)                 // BRK Implied $00 - - - - - - -

OPCODE(BranchonoVerflowClear, 0x50, opBranchOnOverflowClear, IMP) // BVC $NN Relative $50 - - - - - - -

OPCODE(BranchonoVerflowSet, 0x70, opBranchonOverflowSet, IMP)   // BVS $NN Relative $70 - - - - - - -

OPCODE(CLearCarry, 0x18, opClearCarry, IMP)            // CLC Implied $18 C- - - - - -
OPCODE(CLearDecimal, 0xd8, opClearDecimal, IMP)          // CLD Implied $d8 - - - D- - - Clear Decimal
OPCODE(CLearInterrupt, 0x58, opClearInterrupt, IMP)        // CLI Implied $58 - - I- - - -
OPCODE(CLearoVerflow, 0xb8, opClearOverflow, IMP)         // CLV Implied $b8 - - - - - V-

OPCODE(CoMPareacc_I, 0xc9, opCompareAcc, I)          // CMP #$NN Immediate $c9 CZ- - - - N
OPCODE(CoMPareacc_Ab, 0xcd, opCompareAcc, Ab)         // CMP $NNNN Absolute $cd CZ- - - - N
OPCODE(CoMPareacc_AbX, 0xdd, opCompareAcc, AbX)        // CMP $NNNN,X Absolute,X $dd CZ- - - - N
OPCODE(CoMPareacc_AbY, 0xd9, opCompareAcc, AbY)        // CMP $NNNN,Y Absolute,Y $d9 CZ- - - - N
OPCODE(CoMPareacc_Z, 0xc5, opCompareAcc, Z)          // CMP $NN Zero Page $c5 CZ- - - - N
OPCODE(CoMPareacc_ZX, 0xd5, opCompareAcc, ZX)         // CMP $NN,X Zero Page,X $d5 CZ- - - - N
OPCODE(CoMPareacc_IndexIndir, 0xc1, opCompareAcc, IndexIndir) // CMP ($NN,X) Indexed Indirect $c1 CZ- - - - N
OPCODE(CoMPareacc_IndirIndex, 0xd1, opCompareAcc, IndirIndex) // CMP ($NN),Y Indirect Indexed $d1 CZ- - - - N

OPCODE(ComPareX_I, 0xe0, opCompareX, I)          // CPX #$NN Immediate $e0 CZ- - - - N
OPCODE(ComPareX_Ab, 0xec, opCompareX, Ab)         // CPX $NNNN Absolute $ec CZ- - - - N
OPCODE(ComPareX_Z, 0xe4, opCompareX, Z)          // CPX $NN Zero Page $e4 CZ- - - - N

OPCODE(ComPareY_I, 0xc0, opCompareY, I)          // CPY #$NN Immediate $c0 CZ- - - - N
OPCODE(ComPareY_Ab, 0xcc, opCompareY, Ab)         // CPY $NNNN Absolute $cc CZ- - - - N
OPCODE(ComPareY_Z, 0xc4, opCompareY, Z)          // CPY $NN Zero Page $c4 CZ- - - - N

OPCODE(DECrement_Ab, 0xce, opDecrement, Ab)         // DEC $NNNN Absolute $ce - Z- - - - N
OPCODE(DECrement_AbX, 0xde, opDecrement, AbX)        // DEC $NNNN,X Absolute,X $de - Z- - - - N
OPCODE(DECrement_Z, 0xc6, opDecrement, Z)          // DEC $NN Zero Page $c6 - Z- - - - N
OPCODE(DECrement_ZX, 0xd6, opDecrement, ZX)         // DEC $NN,X Zero Page,X $d6 - Z- - - - N

OPCODE(DEcrementX, 0xca, opDecrementX, IMP)            // DEX Implied $ca - Z- - - - N
OPCODE(DEcrementY, 0x88, opDecrementY, IMP)            // DEY Implied $88 - Z- - - - N

OPCODE(ExclusiveOR_I, 0x49, opExclusiveOR, I)          // EOR #$NN Immediate $49 - Z- - - - N
OPCODE(ExclusiveOR_Ab, 0x4d, opExclusiveOR, Ab)         // EOR $NNNN Absolute $4d - Z- - - - N
OPCODE(ExclusiveOR_AbX, 0x5d, opExclusiveOR, AbX)        // EOR $NNNN,X Absolute,X $5d - Z- - - - N
OPCODE(ExclusiveOR_AbY, 0x59, opExclusiveOR, AbY)        // EOR $NNNN,Y Absolute,Y $59 - Z- - - - N
OPCODE(ExclusiveOR_Z, 0x45, opExclusiveOR, Z)          // EOR $NN Zero Page $45 - Z- - - - N
OPCODE(ExclusiveOR_ZX, 0x55, opExclusiveOR, ZX)         // EOR $NN,X Zero Page,X $55 - Z- - - - N
OPCODE(ExclusiveOR_IndexIndir, 0x41, opExclusiveOR, IndexIndir) // EOR ($NN,X) Indexed Indirect $41 - Z- - - - N
OPCODE(ExclusiveOR_IndirIndex, 0x51, opExclusiveOR, IndirIndex) // EOR ($NN),Y Indirect Indexed $51 - Z- - - - N

OPCODE(INCrement_Ab, 0xee, opIncrement, Ab)         // INC $NNNN Absolute $ee - Z- - - - N
OPCODE(INCrement_AbX, 0xfe, opIncrement, AbX)        // INC $NNNN,X Absolute,X $fe - Z- - - - N
OPCODE(INCrement_Z, 0xe6, opIncrement, Z)          // INC $NN Zero Page $e6 - Z- - - - N
OPCODE(INCrement_ZX, 0xf6, opIncrement, ZX)         // INC $NN,X Zero Page,X $f6 - Z- - - - N

OPCODE(INcrementX, 0xe8, opIncrementX, IMP)            // INX Implied $e8 - Z- - - - N
OPCODE(INcrementY, 0xc8, opIncrementY, IMP)            // INY Implied $c8 - Z- - - - N

OPCODE(JuMP_Ab, 0x4c, opJump, Ab)             // JMP $NNNN Absolute $4c - - - - - - -
OPCODE(JuMP_Indir, 0x6c, opJump, IMP)          // JMP $NN Indirect $6c - - - - - - -

OPCODE(JumptoSubRoutine_Ab, 0x20, opJumpToSubroutine, Ab) // JSR $NNNN Absolute $20 - - - - - - -

OPCODE(LoaDAcc_I, 0xa9, opLoadAcc, I)          // LDA #$NN Immediate $a9 - Z- - - - N
OPCODE(LoaDAcc_Ab, 0xad, opLoadAcc, Ab)         // LDA $NNNN Absolute $ad - Z- - - - N
OPCODE(LoaDAcc_AbX, 0xbd, opLoadAcc, AbX)        // LDA $NNNN,X Absolute,X $bd - Z- - - - N
OPCODE(LoaDAcc_AbY, 0xb9, opLoadAcc, AbY)        // LDA $NNNN,Y Absolute,Y $b9 - Z- - - - N
OPCODE(LoaDAcc_Z, 0xa5, opLoadAcc, Z)          // LDA $NN Zero Page $a5 - Z- - - - N
OPCODE(LoaDAcc_ZX, 0xb5, opLoadAcc, ZX)         // LDA $NN,X Zero Page,X $b5 - Z- - - - N
OPCODE(LoaDAcc_IndexIndir, 0xa1, opLoadAcc, IndexIndir) // LDA ($NN,X) Indexed Indirect $a1 - Z- - - - N
OPCODE(LoaDAcc_IndirIndex, 0xb1, opLoadAcc, IndirIndex) // LDA ($NN),Y Indirect Indexed $b1 - Z- - - - N

OPCODE(LoaDX_I, 0xa2, opLoadX, I)          // LDX #$NN Immediate $a2 - Z- - - - N
OPCODE(LoaDX_Ab, 0xae, opLoadX, Ab)         // LDX $NNNN Absolute $ae - Z- - - - N
OPCODE(LoaDX_AbY, 0xbe, opLoadX, AbY)        // LDX $NNNN,Y Absolute,Y $be - Z- - - - N
OPCODE(LoaDX_Z, 0xa6, opLoadX, Z)          // LDX $NN Zero Page $a6 - Z- - - - N
OPCODE(LoaDX_ZY, 0xb6, opLoadX, IMP)         // LDX $NN,Y Zero Page,Y $b6 - Z- - - - N

OPCODE(LoaDY_I, 0xa0, opLoadY, I)          // LDY #$NN Immediate $a0 - Z- - - - N
OPCODE(LoaDY_Ab, 0xac, opLoadY, Ab)         // LDY $NNNN Absolute $ac - Z- - - - N
OPCODE(LoaDY_AbX, 0xbc, opLoadY, AbX)        // LDY $NNNN,X Absolute,X $bc - Z- - - - N
OPCODE(LoaDY_Z, 0xa4, opLoadY, Z)          // LDY $NN Zero Page $a4 - Z- - - - N
OPCODE(LoaDY_ZX, 0xb4, opLoadY, ZX)         // LDY $NN,X Zero Page,X $b4 - Z- - - - N

OPCODE(LogicalShiftRight_Acc, 0x4a, opLogicalShiftRight, IMP)        // LSR A Accumulator $4a CZ- - - - N
OPCODE(LogicalShiftRight_Ab, 0x4e, opLogicalShiftRight, Ab)         // LSR $NNNN Absolute $4e CZ- - - - N
OPCODE(LogicalShiftRight_AbX, 0x5e, opLogicalShiftRight, AbX)        // LSR $NNNN,X Absolute,X $5e CZ- - - - N
OPCODE(LogicalShiftRight_Z, 0x46, opLogicalShiftRight, Z)          // LSR $NN Zero Page $46 CZ- - - - N
OPCODE(LogicalShiftRight_ZX, 0x56, opLogicalShiftRight, ZX)         // LSR $NN,X Zero Page,X $56 CZ- - - - N

OPCODE(NoOPeration, 0xea, opNoop, IMP)            // NOP Implied $ea - - - - - - -

OPCODE(ORwithAcc_I, 0x09, opORwithAcc, I)          // ORA #$NN Immediate $09 - Z- - - - N
OPCODE(ORwithAcc_Ab, 0x0d, opORwithAcc, Ab)         // ORA $NNNN Absolute $0d - Z- - - - N
OPCODE(ORwithAcc_AbX, 0x1d, opORwithAcc, AbX)        // ORA $NNNN,X Absolute,X $1d - Z- - - - N
OPCODE(ORwithAcc_AbY, 0x19, opORwithAcc, AbY)        // ORA $NNNN,Y Absolute,Y $19 - Z- - - - N
OPCODE(ORwithAcc_Z, 0x05, opORwithAcc, Z)          // ORA $NN Zero Page $05 - Z- - - - N
OPCODE(ORwithAcc_ZX, 0x15, opORwithAcc, ZX)         // ORA $NN,X Zero Page,X $15 - Z- - - - N
OPCODE(ORwithAcc_IndexIndir, 0x01, opORwithAcc, IndexIndir) // ORA ($NN,X) Indexed Indirect $01 - Z- - - - N
OPCODE(ORwithAcc_IndirIndex, 0x11, opORwithAcc, IndirIndex) // ORA ($NN),Y Indirect Indexed $11 - Z- - - - N

OPCODE(PusHAcc, 0x48, opPushAcc, IMP)               // PHA Implied $48 - - - - - - -
OPCODE(PusHProcessorstatus, 0x08, opPushProcessorStatus, IMP)   // PHP Implied $08 - - - - - - -
OPCODE(PuLlAcc, 0x68, opPullAcc, IMP)               // PLA Implied $68 - Z- - - - N
OPCODE(PuLlProcessorstatus, 0x28, opPullProcessorStatus, IMP)   // PLP Implied $28 CZIDBVN

OPCODE(ROtateLeft_Acc, 0x2a, opRotateLeft, IMP)        // ROL A Accumulator $2a CZ- - - - N
OPCODE(ROtateLeft_Ab, 0x2e, opRotateLeft, Ab)         // ROL $NNNN Absolute $2e CZ- - - - N
OPCODE(ROtateLeft_AbX, 0x3e, opRotateLeft, AbX)        // ROL $NNNN,X Absolute,X $3e CZ- - - - N
OPCODE(ROtateLeft_Z, 0x26, opRotateLeft, Z)          // ROL $NN Zero Page $26 CZ- - - - N
OPCODE(ROtateLeft_ZX, 0x36, opRotateLeft, ZX)         // ROL $NN,X Zero Page,X $36 CZ- - - - N

OPCODE(ROtateRight_Acc, 0x6a, opRotateRight, IMP)        // ROR A Accumulator $6a CZ- - - - N
OPCODE(ROtateRight_Ab, 0x6e, opRotateRight, Ab)         // ROR $NNNN Absolute $7e CZ- - - - N
OPCODE(ROtateRight_AbX, 0x7e, opRotateRight, AbX)        // ROR $NNNN,X Absolute,X $6e CZ- - - - N
OPCODE(ROtateRight_Z, 0x66, opRotateRight, Z)          // ROR $NN Zero Page $66 CZ- - - - N
OPCODE(ROtateRight_ZX, 0x76, opRotateRight, ZX)         // ROR $NN,X Zero Page,X $76 CZ- - - - N

OPCODE(ReTurnfromInterrupt, 0x40, opReturnfromInterrupt, IMP)          // RTI Implied $40 - - - - - - -
OPCODE(ReTurnfromSubroutine, 0x60, opReturnfromSubroutine, IMP)         // RTS Implied $60 - - - - - - -

OPCODE(SuBtractwithCarry_I, 0xe9, opSubtractWithCarry, I)          // SBC #$NN Immediate $e9 CZ- - - VN
OPCODE(SuBtractwithCarry_Ab, 0xed, opSubtractWithCarry, Ab)         // SBC $NNNN Absolute $ed CZ- - - VN
OPCODE(SuBtractwithCarry_AbX, 0xfd, opSubtractWithCarry, AbX)        // SBC $NNNN,X Absolute,X $fd CZ- - - VN
OPCODE(SuBtractwithCarry_AbY, 0xf9, opSubtractWithCarry, AbY)        // SBC $NNNN,Y Absolute,Y $f9 CZ- - - VN
OPCODE(SuBtractwithCarry_Z, 0xe5, opSubtractWithCarry, Z)          // SBC $NN Zero Page $e5 CZ- - - VN
OPCODE(SuBtractwithCarry_ZX, 0xf5, opSubtractWithCarry, ZX)         // SBC $NN,X Zero Page,X $f5 CZ- - - VN
OPCODE(SuBtractwithCarry_IndexIndir, 0xe1, opSubtractWithCarry,
       IndexIndir) // SBC ($NN,X) Indexed Indirect $e1 CZ- - - VN
OPCODE(SuBtractwithCarry_IndirIndex, 0xf1, opSubtractWithCarry,
       IndirIndex) // SBC ($NN),Y Indirect Indexed $f1 CZ- - - VN

OPCODE(SEtCarry, 0x38, opSetCarry, IMP)            // SEC Implied $38 C- - - - - -
OPCODE(SEtDecimal, 0xf8, opSetDecimal, IMP)          // SED Implied $f8 - - - D- - -
OPCODE(SEtInterrupt, 0x78, opSetInterrupt, IMP)        // SEI Implied $78 - - I- - - -

OPCODE(SToreAcc_Ab, 0x8d, opStoreAcc, Ab)         // STA $NNNN Absolute $8d - - - - - - -
OPCODE(SToreAcc_AbX, 0x9d, opStoreAcc, AbX)        // STA $NNNN,X Absolute,X $9d - - - - - - -
OPCODE(SToreAcc_AbY, 0x99, opStoreAcc, AbY)        // STA $NNNN,Y Absolute,Y $99 - - - - - - -
OPCODE(SToreAcc_Z, 0x85, opStoreAcc, Z)          // STA $NN Zero Page $85 - - - - - - -
OPCODE(SToreAcc_ZX, 0x95, opStoreAcc, ZX)         // STA $NN,X Zero Page,X $95 - - - - - - -
OPCODE(SToreAcc_IndexIndir, 0x81, opStoreAcc, IndexIndir) // STA ($NN,X) Indexed Indirect $81 - - - - - - -
OPCODE(SToreAcc_IndirIndex, 0x91, opStoreAcc, IndirIndex) // STA ($NN),Y Indirect Indexed $91 - - - - - - -

OPCODE(SToreX_Ab, 0x8e, opStoreX, Ab)         // STX $NNNN Absolute $8e - - - - - - -
OPCODE(SToreX_Z, 0x86, opStoreX, Z)          // STX $NN Zero Page $86 - - - - - - -
OPCODE(SToreX_ZY, 0x96, opStoreX, IMP)         // STX $NN,Y Zero Page,Y $96 - - - - - - -

OPCODE(SToreY_Ab, 0x8c, opStoreY, Ab)         // STY $NNNN Absolute $8c - - - - - - -
OPCODE(SToreY_Z, 0x84, opStoreY, Z)          // STY $NN Zero Page $84 - - - - - - -
OPCODE(SToreY_ZX, 0x94, opStoreY, ZX)         // STY $NN,X Zero Page,X $94 - - - - - - -

OPCODE(TransferAtoX, 0xaa, opTransferAtoX, IMP)            // TAX Implied $aa - Z- - - - N
OPCODE(TransferAtoY, 0xa8, opTransferAtoY, IMP)            // TAY Implied $a8 - Z- - - - N
OPCODE(TransferStacktoX, 0xba, opTransferStacktoX, IMP)        // TSX Implied $ba - Z- - - - N
OPCODE(TransferXtoA, 0x8a, opTransferXtoA, IMP)            // TXA Implied $8a - Z- - - - N
OPCODE(TransferXtoStack, 0x9a, opTransferXtoStack, IMP)        // TXS Implied $9a - - - - - - -
OPCODE(TransferYtoA, 0x98, opTransferYtoA, IMP)            // TYA Implied $98 - Z- - - - N
#undef OPCODE