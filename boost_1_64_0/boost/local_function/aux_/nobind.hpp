
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_

#include <boost/local_function/config.hpp>

// NOTE: The current implementation needs no-bind placeholders only when
// local types cannot be passed as template parameters.
#if !BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS

namespace boost { namespace local_function { namespace aux {

typedef int nobind_t; // Tag no-bind type.

static nobind_t nobind; // Global variable so all no-binds can reference it.

// NOTE: Used only to get rid of unused static variable `nobind` (this function
// is never actually called so it does not need to be defined).
void no_unused_nobind_warning_(nobind_t* ptr = &nobind);

} } } // namespace

#endif // locals as tparams

#endif // #include guard


/* nobind.hpp
+zmuyu7NdZ7nrv1+++pEOJQwhefKrmun/h179ek/aHTOJMt9Kmvbbe1xWq5/cAOxA2D/XCCsf780MyHYfom8WMqDNGWdvXe/1EsaCGsYSFHNg1XXWmx7rfJctF6vpV9qUmjE+VR7kPtxC3LQaa8su7Kw7JXwufK/QU/j/w+ROPqGhkgzxK68RJ+sE1arW0bm9Md+oMVO1OUqb/uVLeNZyHpkDyK2L8x7PFneSw4hEJvbhntwdkPPU/6q7YWtl9+6fe7bU7IPfoooboaMIG7+er/6yB1j887nsS0zT4VvwrO1gl0diD7r2vNBIzPt2qNt2JzmTt8uEtZq1yBVs1/TTljnd5hYuEz5RwfZ7qUcrLYI5Nq8bRFwDf62CFI99fOy1M9LPvVTUMnfNuIc+tUiv/oZPCYrK7B3Fndc3fdb6IL6P2teIyV2nKUfm1bbWNzgm1fs8WmW76gA0ramczjG3w5Hf9psbb90xmSNpYad3qsbqPD32JWR6NJNG+SjaihRz+BFCe7n8asB7HHhV2ZS39dvsDxHZW1/kct5rXtcBcN9+rNP7Pl8U0rKtE09Jw67/5mjTmvdndfS36XCnz2wIfKvd03Lv3b/6QHDbmlQzPpl5X5Nt0GJh/qcahKVk1Q85fIz65zX/E8PM9wX3vhueIX7/vVy3eUf1E1+6vp2zmvmDyvbBLs2uo5kRVRMXNlw7LBhV1TNp70rGwE779i15Zfv556aNKdWtdfzbinrtLbfydZA8DYOVmuGe0mHPyeNS34g762Etg9EFf/8tZrvj3vi+sl5Z+v1WTtj4vWv3vfmK9uYN6nKPzdx1vfTuj9+872Nb3oqpkXUYWdbDI+q/D//tyWd7gkP+7nDoFYvjPqs1QDaj9LT9ofki3udnjxj6bU3JxyNmMME5GoVDfdFrz6+fufWv5y5I25llUsif+hKeSo9R/NqP3HpxlFnp51cvOruxbWYMNJVN9xzikbe933JxVt2PdQxqcmh1uucbBMEb4vB3gZE8DYUTsu8NQ41hrIPNkUay9/zkCby92WIrOGQ8SA1doafzxoOTdZwwCrwn7A6dOnuuSz/4rwePAtHwF/gNKjjf6+E88wZXSbp1Jd0rHNG/yrpPAHj4AJYGz4p+p/SZM4zUix6/iJ6yiOZomeR6FkCG8BnYHP4LGwHn4NXw+dhN/gC7A5fhP3gSzAbvgxz4CuSbmvPNyVMknTDkSaSLv5TDbaBUWps010+V0j8obp878h3ohG/MdJP5hiSN7UGqT2sBK+Fl8Pr4ZUwHXaE3SXfPeAtsCccr+rLPcc+H06GfeBMeDPMN9KBT8Lb4ELYH66CGXADHAA3SfzNcBh8D+bCPXAcLIbj4XdwAvwR3g7LG3NXYUU4GTaEd8LG8C54GZwCW8MRsD3MhlfBkfBaOAr2hKNhH3gf7A9nwlw4G06D98PZ8AH4EMyHD8O5cKE6l7nFnm8NWEHqy2UZj3hY6mueZlmDL+FjJbx1zfZrEv51GA2XS7zORCiWeN2lXhsibT1zR6U9rtZkLaImaxFhB7hB2mMJ7AzfhT3gJtgbboYZcAscCLfCTPgeHA63wTvhTjgd7oJz4B74OPwAPgX3Sr1/ApfDz+BqeBiuh5/D7fALuAN+CT+RfBXD/fA0/FDq/SPNPXf3AKwGjXAJ8CisA4/BS8S9KTwOW8j55fBN2BWugelud5lrJ++OUif7fObaldHd9VAWxhp+sDaMhE1gBXgpjIbN5Nxz/xaJ3po292+q1O9lcv+2gEnwckv70OQ9Is6mfVwq8ZvCWNjM0l/VlnizbPqrKtI+qkq6NaGh8yLYzIgL02EdOATWg6NhAzgBXgzvho3kfqdtqTU=
*/