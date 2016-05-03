/**
 * Support for CBLAS, C binding to Basic Linear Algebra Subprograms originally
 * written in Fortran 77. Linking to Intel's MKL should be transparent through
 * C into Lua. NVidia's CUDA implementation is stateful, however, and requires
 * extra wrapping.
 *
 * TODO: The BLAS header does not allow an alternate complex specification the
 * way that LAPACK does, so the script needs to prefix complex arrays with the
 * __unm operator for it to pass a void pointer. Otherwise we need to wrap all
 * the complex BLAS functions by hand. My "blas.hpp" header mediates the issue
 * but does not seem to be an optimal solution either.
 */

#include "lux/lux.hpp"
#include <cblas.h>
#include <complex>

template <class real> using complex = std::complex<real>;

// EXCEPTIONS /////////////////////////////////////////////////////////////////

// SINGLE PRECISION COMPLEX

static inline
complex<float> cdotu(const int N, const complex<float> *X, const int incX, const complex<float> *Y, const int incY)
{
	complex<float> dotu;
	cblas_cdotu_sub(N, X, incX, Y, incY, &dotu);
	return dotu;
}

static inline
complex<float> cdotc(const int N, const complex<float> *X, const int incX, const complex<float> *Y, const int incY)
{
	complex<float> dotc;
	cblas_cdotc_sub(N, X, incX, Y, incY, &dotc);
	return dotc;
}

// DOUBLE PRECISION COMPLEX

static inline
complex<double> zdotu(const int N, const complex<double> *X, const int incX, const complex<double> *Y, const int incY)
{
	complex<double> dotu;
	cblas_zdotu_sub(N, X, incX, Y, incY, &dotu);
	return dotu;
}

static inline
complex<double> zdotc(const int N, const complex<double> *X, const int incX, const complex<double> *Y, const int incY)
{
	complex<double> dotc;
	cblas_zdotc_sub(N, X, incX, Y, incY, &dotc);
	return dotc;
}

// MODULE ENTRY POINT /////////////////////////////////////////////////////////

#define REG(reg) {#reg, lux_cast(cblas_##reg)},

extern "C" int luaopen_blas(lua_State *state)
{
	luaL_Reg regs[] =
	{
		// SINGLE PRECISION FLOAT
		
		// LEVEL 1
		REG(sdsdot)
		REG(dsdot)
		REG(sdot)
		REG(snrm2)
		REG(sasum)
		REG(isamax)
		REG(sswap)
		REG(scopy)
		REG(saxpy)
		REG(srotg)
		REG(srotmg)
		REG(srot)
		REG(srotm)
		REG(sscal)
		// LEVEL 2
		REG(sgemv)
		REG(sgbmv)
		REG(strmv)
		REG(stbmv)
		REG(stpmv)
		REG(strsv)
		REG(stbsv)
		REG(stpsv)
		REG(ssymv)
		REG(ssbmv)
		REG(sspmv)
		REG(sger)
		REG(ssyr)
		REG(sspr)
		REG(ssyr2)
		REG(sspr2)
		// LEVEL 3
		REG(sgemm)
		REG(ssymm)
		REG(ssyrk)
		REG(ssyr2k)
		REG(strmm)
		REG(strsm)
	
		// DOUBLE PRECISION FLOAT
	
		// LEVEL 1
		REG(ddot)
		REG(dnrm2)
		REG(dasum)
		REG(idamax)
		REG(dswap)
		REG(dcopy)
		REG(daxpy)
		REG(drotg)
		REG(drotmg)
		REG(drot)
		REG(drotm)
		REG(dscal)
		// LEVEL 2
		REG(dgemv)
		REG(dgbmv)
		REG(dtrmv)
		REG(dtbmv)
		REG(dtpmv)
		REG(dtrsv)
		REG(dtbsv)
		REG(dtpsv)
		REG(dsymv)
		REG(dsbmv)
		REG(dspmv)
		REG(dger)
		REG(dsyr)
		REG(dspr)
		REG(dsyr2)
		REG(dspr2)
		// LEVEL 3
		REG(dgemm)
		REG(dsymm)
		REG(dsyrk)
		REG(dsyr2k)
		REG(dtrmm)
		REG(dtrsm)
	
		// SINGLE PRECISION COMPLEX

		// LEVEL 1
		{"cdotu", lux_cast(cdotu)},
		{"cdotc", lux_cast(cdotc)},
		REG(scnrm2)
		REG(scasum)
		REG(icamax)
		REG(cswap)
		REG(ccopy)
		REG(caxpy)
		REG(cscal)
		// LEVEL 2
		REG(cgemv)
		REG(cgbmv)
		REG(ctrmv)
		REG(ctbmv)
		REG(ctpmv)
		REG(ctrsv)
		REG(ctbsv)
		REG(ctpsv)
		REG(chemv)
		REG(chbmv)
		REG(chpmv)
		REG(cgeru)
		REG(cgerc)
		REG(cher)
		REG(chpr)
		REG(cher2)
		REG(chpr2)
		// LEVEL 3
		REG(cgemm)
		REG(csymm)
		REG(chemm)
		REG(csyrk)
		REG(cherk)
		REG(csyr2k)
		REG(cher2k)
		REG(ctrmm)
		REG(ctrsm)
	
		// DOUBLE PRECISION COMPLEX

		// LEVEL 1
		{"zdotu", lux_cast(zdotu)},
		{"zdotc", lux_cast(zdotc)},
		REG(dznrm2)
		REG(dzasum)
		REG(izamax)
		REG(zswap)
		REG(zcopy)
		REG(zaxpy)
		REG(zscal)
		// LEVEL 2
		REG(zgemv)
		REG(zgbmv)
		REG(ztrmv)
		REG(ztbmv)
		REG(ztpmv)
		REG(ztrsv)
		REG(ztbsv)
		REG(ztpsv)
		REG(zhemv)
		REG(zhbmv)
		REG(zhpmv)
		REG(zgeru)
		REG(zgerc)
		REG(zher)
		REG(zhpr)
		REG(zher2)
		REG(zhpr2)
		// LEVEL 3
		REG(zgemm)
		REG(zsymm)
		REG(zhemm)
		REG(zsyrk)
		REG(zherk)
		REG(zsyr2k)
		REG(zher2k)
		REG(ztrmm)
		REG(ztrsm)
		
		// END
		
		{nullptr}
	};
	luaL_newlib(state, regs); 
	return 1;
}

