// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_upper_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_upper_bound
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_upper_bound.hpp
/Fnly89Sv2t8tGXcTn6+9TX5JRmSE3LSGLdVhged6Er9qtvTUEtZq2vzLiTvMCfyVgYvLWcMlvpeKzGESgw1SW8RQ6Q2BmlVzudnqu8stL/3Vp1/yF3afXgH+U/Q5C/fFsq5vS3fi/J18nuN/PK0+U3LSeVvVkpOdlLGjHQX6lmvnXn7avfjneS7WpOvshsrXyBdaWd6ZZ5nn7eUuchx3gw6Pd2QVs58lfMEWbKa5OtB2kW+xTr58h3edDtyRpILedKeNWU1+mm379vkeUGbp2nA62RrLTufr+7nn/3zCqSOfcMd5MsubcxOuak8R/vrt+VIh3lyiuLCOapeOy7x1/Z7KCLPWNs80zISkiRT/s3ZhWnPdaUd6/XD6NXDPAq0nK/KPGMC1Wj7XVyeX5Ar38Vn4h7TPm4bI4+NMscTeIN7vs82ZrnSe76jSqc/Uqat9xLb3E8v52aUQcak7uj3YgPz95935PuPpR9LYKD2M2Av7wlrahNrFk8LMFWhy/Wnbi8rJa8Gkld90nvkFWmXV3nP0ey32QamWUuW/bMOm9bQ7iv7TMd8uzhu9pzmX7zdB3gUZRrAcaqCBFKAFIqEDhIgNAlICU2KlAARQ01CsiGBlCUFQhECAoYeFAVUNAh2PaOioogGRUFFiSJYDs9Yz4Jn5FA5Rb3/7L4zmbYhu/GO5xl+7LLfvO988803fca8v1PX9Q6IWsb1X3Pr+u91pa1Ycunl8zakGv80pRY5jccSx8hz+Qsk/gqGocQvscSPT0x3ZipvjsjN8mIdaJ4njSmljiO48p0a8h3dfqZ2HNHjewPeJL+Yrrb58Y907hZgA6UG9XSYz4xAjndqz/83zDdniFyXy1BX8ntLmW+mvGTb1Kt3GZCP4T0AcwM856Ot60Ks9XRCmY+mfHzdVjbPxyRKyTgMy9b2UOuy9Q7fldvmYVkJep2PWke7Ay9dR13k3QKrZN/8Rrlnr9ZV5txk2951x4v3++dqTs+46ii78n4Z5fMC47smyySnWVJfMxhOKvPNJidqS9vb12rMh3kYLPm14HPlaOzrTjsf0sLUT0ndRXazyZNO11V13BHjyzEp/TrXvXY11tmZFuY2JsfFLLnIfstfkJO+jae2tG73nFKWfVP8v2qfTXsfiLRx/T7cRXMusi4rrkYuNdmH06/T8kx9wCY5uTBZlrMJMn9KPeakbZOmZftwPEw9JjfVtb7PWpDnNObTqrV9PpERl8qHtuLFu9Gqm8/O1qb9Icmn+JL5KEuDb9tg2vGNK63rrfdDmTem2L7sbxPPbn/b0q/o62K/5DNQ8oli+JB8Kqz5zHNkOrI5pqVujHK21bvc9O32d1mn6tcPUW2s/crfySW6uyWXjJx5NV9n/SI56OvjvTbW9fjH5JBgzSGT9xu5t8cqt3p8zuVFz+tPra/JD7fm9gm5FVWVWw73odN6c9NyHDXt/56vIscpkmNAW+s8/FRp3zY5ZuXGZzty8jI4FO9uVDVcr6p5Rkqe+uWuSPLqKX1QNzlnUW7NS44zed/vWM5J6/vAdtZ76j8nfngPS3wnN7wnpac5MnN9ODZhzqVBoLWNP2iTy5fkEm2bi7wX+S/IpZHNfIlob9qukfM1CTa55GU7s3K83HbQP+8gl0FGYti2OtDeWh9fKcuVKYeaHBOUujDkohyNAePx/g7W5edrcikx5VLT44TmeZMufaG+XsqsuVAvfG/KpSbHDe3qRcZhqJf8ju7CcZLLNNlPrrDLRVZPrrvOcx35vpwj1e8v5zAmvjPsL8t3TG+mYR0W0Mk90jXSzxQwfEueCT2teXLMkwVLydX7vkbyszvuJPs5xnm5s5N1Xp4NJd9IS168GC4=
*/