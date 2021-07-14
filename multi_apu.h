
// Am9511A functions in assembly

// unload the APU stack, to return a result

extern float pop_0(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern float pop_1(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern float pop_2(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern float pop_3(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;

// load the stack

extern void push_0(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void push_1(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void push_2(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void push_3(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;


// allow chaining by not returning a result

extern void add_0(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void add_1(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void add_2(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void add_3(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;

extern void mul_0(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void mul_1(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void mul_2(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void mul_3(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;

extern void div_0(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void div_1(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void div_2(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void div_3(float y) __preserves_regs(iyh,iyl) __z88dk_fastcall;


// trig functions
// assume stack loaded

extern void sin_0(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void sin_1(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void sin_2(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void sin_3(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;

extern void cos_0(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void cos_1(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void cos_2(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void cos_3(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;

extern void tan_0(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void tan_1(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void tan_2(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;
extern void tan_3(void) __preserves_regs(b,c,d,e,h,l,iyh,iyl) __z88dk_fastcall;

// allow chaining by not returning a result

extern void asin_0(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void asin_1(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void asin_2(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void asin_3(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;

extern void acos_0(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void acos_1(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void acos_2(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void acos_3(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;

extern void atan_0(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void atan_1(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void atan_2(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void atan_3(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;


// degrees to radians
// allow chaining by not returning a result

extern void rad_0(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void rad_1(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void rad_2(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void rad_3(float x) __preserves_regs(iyh,iyl) __z88dk_fastcall;

// radians to degrees
// assume stack loaded

extern void deg_0(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void deg_1(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void deg_2(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;
extern void deg_3(void) __preserves_regs(iyh,iyl) __z88dk_fastcall;

