;
;  Calculate sine, cosine, and tangental functions
;  using the Am9511A APU
;

include "config_rc2014_private.inc"

EXTERN  asm_am9511_0_pushf_hl, asm_am9511_0_pushf_fastcall
EXTERN  asm_am9511_0_popf_hl,  asm_am9511_0_popf

EXTERN  asm_am9511_1_pushf_hl, asm_am9511_1_pushf_fastcall
EXTERN  asm_am9511_1_popf_hl,  asm_am9511_1_popf

EXTERN  asm_am9511_2_pushf_hl, asm_am9511_2_pushf_fastcall
EXTERN  asm_am9511_2_popf_hl,  asm_am9511_2_popf

EXTERN  asm_am9511_3_pushf_hl, asm_am9511_3_pushf_fastcall
EXTERN  asm_am9511_3_popf_hl,  asm_am9511_3_popf

;==============================================================================

SECTION code_user

PUBLIC _pop_0
PUBLIC _pop_1
PUBLIC _pop_2
PUBLIC _pop_3

defc _pop_0 = asm_am9511_0_popf
defc _pop_1 = asm_am9511_1_popf
defc _pop_2 = asm_am9511_2_popf
defc _pop_3 = asm_am9511_3_popf


PUBLIC _push_0
PUBLIC _push_1
PUBLIC _push_2
PUBLIC _push_3

defc _push_0 = asm_am9511_0_pushf_fastcall
defc _push_1 = asm_am9511_1_pushf_fastcall
defc _push_2 = asm_am9511_2_pushf_fastcall
defc _push_3 = asm_am9511_3_pushf_fastcall

;==============================================================================

SECTION code_user

PUBLIC _add_0
PUBLIC _add_1
PUBLIC _add_2
PUBLIC _add_3

._add_0
    call asm_am9511_0_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FADD
    out (__IO_APU0_CONTROL),a           ; (x*y)
    ret

._add_1
    call asm_am9511_1_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FADD
    out (__IO_APU1_CONTROL),a           ; (x*y)
    ret

._add_2
    call asm_am9511_2_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FADD
    out (__IO_APU2_CONTROL),a           ; (x*y)
    ret

._add_3
    call asm_am9511_3_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FADD
    out (__IO_APU3_CONTROL),a           ; (x*y)
    ret

PUBLIC _mul_0
PUBLIC _mul_1
PUBLIC _mul_2
PUBLIC _mul_3

._mul_0
    call asm_am9511_0_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU0_CONTROL),a           ; (x*y)
    ret

._mul_1
    call asm_am9511_1_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU1_CONTROL),a           ; (x*y)
    ret

._mul_2
    call asm_am9511_2_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU2_CONTROL),a           ; (x*y)
    ret

._mul_3
    call asm_am9511_3_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU3_CONTROL),a           ; (x*y)
    ret

PUBLIC _div_0
PUBLIC _div_1
PUBLIC _div_2
PUBLIC _div_3

._div_0
    call asm_am9511_0_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FDIV
    out (__IO_APU0_CONTROL),a           ; (x/y)
    ret

._div_1
    call asm_am9511_1_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FDIV
    out (__IO_APU1_CONTROL),a           ; (x/y)
    ret

._div_2
    call asm_am9511_2_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FDIV
    out (__IO_APU2_CONTROL),a           ; (x/y)
    ret

._div_3
    call asm_am9511_3_pushf_fastcall    ; y
    ld a,__IO_APU_OP_FDIV
    out (__IO_APU3_CONTROL),a           ; (x/y)
    ret

;==============================================================================

SECTION code_user

PUBLIC _sin_0
PUBLIC _sin_1
PUBLIC _sin_2
PUBLIC _sin_3

._sin_0
    ld a,__IO_APU_OP_SIN
    out (__IO_APU0_CONTROL),a           ; sin(x)
    ret

._sin_1
    ld a,__IO_APU_OP_SIN
    out (__IO_APU1_CONTROL),a           ; sin(x)
    ret

._sin_2
    ld a,__IO_APU_OP_SIN
    out (__IO_APU2_CONTROL),a           ; sin(x)
    ret

._sin_3
    ld a,__IO_APU_OP_SIN
    out (__IO_APU3_CONTROL),a           ; sin(x)
    ret


PUBLIC _cos_0
PUBLIC _cos_1
PUBLIC _cos_2
PUBLIC _cos_3

._cos_0
    ld a,__IO_APU_OP_COS
    out (__IO_APU0_CONTROL),a           ; cos(x)
    ret

._cos_1
    ld a,__IO_APU_OP_COS
    out (__IO_APU1_CONTROL),a           ; cos(x)
    ret

._cos_2
    ld a,__IO_APU_OP_COS
    out (__IO_APU2_CONTROL),a           ; cos(x)
    ret

._cos_3
    ld a,__IO_APU_OP_COS
    out (__IO_APU3_CONTROL),a           ; cos(x)
    ret


PUBLIC _tan_0
PUBLIC _tan_1
PUBLIC _tan_2
PUBLIC _tan_3

._tan_0
    ld a,__IO_APU_OP_TAN
    out (__IO_APU0_CONTROL),a           ; tan(x)
    ret

._tan_1
    ld a,__IO_APU_OP_TAN
    out (__IO_APU1_CONTROL),a           ; tan(x)
    ret

._tan_2
    ld a,__IO_APU_OP_TAN
    out (__IO_APU2_CONTROL),a           ; tan(x)
    ret

._tan_3
    ld a,__IO_APU_OP_TAN
    out (__IO_APU3_CONTROL),a           ; tan(x)
    ret


PUBLIC _asin_0
PUBLIC _asin_1
PUBLIC _asin_2
PUBLIC _asin_3

._asin_0
    call asm_am9511_0_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ASIN
    out (__IO_APU0_CONTROL),a           ; asin(x)
    ret

._asin_1
    call asm_am9511_1_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ASIN
    out (__IO_APU1_CONTROL),a           ; asin(x)
    ret

._asin_2
    call asm_am9511_2_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ASIN
    out (__IO_APU2_CONTROL),a           ; asin(x)
    ret

._asin_3
    call asm_am9511_3_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ASIN
    out (__IO_APU3_CONTROL),a           ; asin(x)
    ret


PUBLIC _acos_0
PUBLIC _acos_1
PUBLIC _acos_2
PUBLIC _acos_3

._acos_0
    call asm_am9511_0_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ACOS
    out (__IO_APU0_CONTROL),a           ; acos(x)
    ret

._acos_1
    call asm_am9511_1_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ACOS
    out (__IO_APU1_CONTROL),a           ; acos(x)
    ret

._acos_2
    call asm_am9511_2_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ACOS
    out (__IO_APU2_CONTROL),a           ; acos(x)
    ret

._acos_3
    call asm_am9511_3_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ACOS
    out (__IO_APU3_CONTROL),a           ; acos(x)
    ret


PUBLIC _atan_0
PUBLIC _atan_1
PUBLIC _atan_2
PUBLIC _atan_3

._atan_0
    call asm_am9511_0_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ATAN
    out (__IO_APU0_CONTROL),a           ; atan(x)
    ret

._atan_1
    call asm_am9511_1_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ATAN
    out (__IO_APU1_CONTROL),a           ; atan(x)
    ret

._atan_2
    call asm_am9511_2_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ATAN
    out (__IO_APU2_CONTROL),a           ; atan(x)
    ret

._atan_3
    call asm_am9511_3_pushf_fastcall    ; x
    ld a,__IO_APU_OP_ATAN
    out (__IO_APU3_CONTROL),a           ; atan(x)
    ret

;==============================================================================

SECTION code_user

PUBLIC _rad_0
PUBLIC _rad_1
PUBLIC _rad_2
PUBLIC _rad_3

._rad_0
    call asm_am9511_0_pushf_fastcall    ; x
    ld de,$3C8E
    ld hl,$FA35
    call asm_am9511_0_pushf_fastcall    ; (M_PI/180.0)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU0_CONTROL),a           ; (x*(M_PI/180.0))
    ret

._rad_1
    call asm_am9511_1_pushf_fastcall    ; x
    ld de,$3C8E
    ld hl,$FA35
    call asm_am9511_1_pushf_fastcall    ; (M_PI/180.0)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU1_CONTROL),a           ; (x*(M_PI/180.0))
    ret

._rad_2
    call asm_am9511_2_pushf_fastcall    ; x
    ld de,$3C8E
    ld hl,$FA35
    call asm_am9511_2_pushf_fastcall    ; (M_PI/180.0)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU2_CONTROL),a           ; (x*(M_PI/180.0))
    ret

._rad_3
    call asm_am9511_3_pushf_fastcall    ; x
    ld de,$3C8E
    ld hl,$FA35
    call asm_am9511_3_pushf_fastcall    ; (M_PI/180.0)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU3_CONTROL),a           ; (x*(M_PI/180.0))
    ret


PUBLIC _deg_0
PUBLIC _deg_1
PUBLIC _deg_2
PUBLIC _deg_3

._deg_0
    ld de,$4265
    ld hl,$2EE0
    call asm_am9511_0_pushf_fastcall    ; (180.0/M_PI)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU0_CONTROL),a           ; (x)*(180.0/M_PI))
    ret

._deg_1
    ld de,$4265
    ld hl,$2EE0
    call asm_am9511_1_pushf_fastcall    ; (180.0/M_PI)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU1_CONTROL),a           ; (x)*(180.0/M_PI))
    ret

._deg_2
    ld de,$4265
    ld hl,$2EE0
    call asm_am9511_2_pushf_fastcall    ; (180.0/M_PI)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU2_CONTROL),a           ; (x)*(180.0/M_PI))
    ret

._deg_3
    ld de,$4265
    ld hl,$2EE0
    call asm_am9511_3_pushf_fastcall    ; (180.0/M_PI)
    ld a,__IO_APU_OP_FMUL
    out (__IO_APU3_CONTROL),a           ; (x)*(180.0/M_PI))
    ret

;==============================================================================

