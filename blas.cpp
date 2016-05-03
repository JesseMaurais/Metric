/**
 * Support for CBLAS, C binding to Basic Linear Algebra Subprograms originally
 * written in Fortran 77. Linking to Intel's MKL should be transparent through
 * C into Lua. NVidia's CUDA implementation is stateful, however, and requires
 * extra wrapping.
 */

#include "lux/lux.hpp"
#include "cblas.hpp"


extern "C" int luaopen_blas(lua_State *state)
{
	luaL_Reg regs[] =
	{
		// SINGLE PRECISION FLOAT

		#define s(reg) {"s" #reg, lux_cast(reg<float>)},
		
		// LEVEL 1
		s(dot)
		s(nrm2)
		s(asum)
		s(iamax)
		s(swap)
		s(copy)
		s(axpy)
		s(rotg)
		s(rotmg)
		s(rot)
		s(rotm)
		s(scal)
		// LEVEL 2
		s(gemv)
		s(gbmv)
		s(trmv)
		s(tbmv)
		s(tpmv)
		s(trsv)
		s(tbsv)
		s(tpsv)
		s(symv)
		s(sbmv)
		s(spmv)
		s(ger)
		s(syr)
		s(spr)
		s(syr2)
		s(spr2)
		// LEVEL 3
		s(gemm)
		s(symm)
		s(syrk)
		s(syr2k)
		s(trmm)
		s(trsm)
	
		// DOUBLE PRECISION FLOAT

		#define d(reg) {"d" #reg, lux_cast(reg<double>)},
	
		// LEVEL 1
		d(dot)
		d(nrm2)
		d(asum)
		d(iamax)
		d(swap)
		d(copy)
		d(axpy)
		d(rotg)
		d(rotmg)
		d(rot)
		d(rotm)
		d(scal)
		// LEVEL 2
		d(gemv)
		d(gbmv)
		d(trmv)
		d(tbmv)
		d(tpmv)
		d(trsv)
		d(tbsv)
		d(tpsv)
		d(symv)
		d(sbmv)
		d(spmv)
		d(ger)
		d(syr)
		d(spr)
		d(syr2)
		d(spr2)
		// LEVEL 3
		d(gemm)
		d(symm)
		d(syrk)
		d(syr2k)
		d(trmm)
		d(trsm)
	
		// SINGLE PRECISION COMPLEX

		#define c(reg) {"c" #reg, lux_cast(reg<complex<float>>)},

		// LEVEL 1
		c(dotu)
		c(dotc)
//		c(nrm2)
		{"cnrm2", lux_cast((nrm2<complex<float>, float>))},
//		c(asum)
		{"casum", lux_cast((asum<complex<float>, float>))},
		c(iamax)
		c(swap)
		c(copy)
		c(axpy)
		c(scal)
		// LEVEL 2
		c(gemv)
		c(gbmv)
		c(trmv)
		c(tbmv)
		c(tpmv)
		c(trsv)
		c(tbsv)
		c(tpsv)
		c(hemv)
		c(hbmv)
		c(hpmv)
		c(geru)
		c(gerc)
//		c(her)
		{"cher", lux_cast(her<float>)},
//		c(hpr)
		{"chpr", lux_cast(hpr<float>)},
		c(her2)
		c(hpr2)
		// LEVEL 3
		c(gemm)
		c(symm)
		c(hemm)
		c(syrk)
//		c(herk)
		{"cherk", lux_cast(herk<float>)},
		c(syr2k)
//		c(her2k)
		{"cher2k", lux_cast(her2k<float>)},
		c(trmm)
		c(trsm)
	
		// DOUBLE PRECISION COMPLEX
	
		#define z(reg) {"z" #reg, lux_cast(reg<complex<double>>)},

		// LEVEL 1
		z(dotu)
		z(dotc)
//		z(nrm2)
		{"znrm2", lux_cast((nrm2<complex<double>, double>))},
//		z(asum)
		{"zasum", lux_cast((asum<complex<double>, double>))},
		z(iamax)
		z(swap)
		z(copy)
		z(axpy)
		z(scal)
		// LEVEL 2
		z(gemv)
		z(gbmv)
		z(trmv)
		z(tbmv)
		z(tpmv)
		z(trsv)
		z(tbsv)
		z(tpsv)
		z(hemv)
		z(hbmv)
		z(hpmv)
		z(geru)
		z(gerc)
//		z(her)
		{"zher", lux_cast(her<double>)},
//		z(hpr)
		{"zhpr", lux_cast(hpr<double>)},
		z(her2)
		z(hpr2)
		// LEVEL 3
		z(gemm)
		z(symm)
		z(hemm)
		z(syrk)
//		z(herk)
		{"zherk", lux_cast(herk<double>)},
		z(syr2k)
//		z(her2k)
		{"zher2k", lux_cast(her2k<double>)},
		z(trmm)
		z(trsm)
		
		// END
		
		{nullptr}
	};
	luaL_newlib(state, regs); 
	return 1;
}

