
#ifndef BOOST_CONTRACT_HPP_
#define BOOST_CONTRACT_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Include all header files required by this library at once (for convenience).

All header files <c>boost/contract/\*.hpp</c> are independent from one another
and can be included one-by-one to reduce the amount of code to compile from this
library in user code (but this was measured to not make an appreciable
difference in compile-time so <c>boost/contract.hpp</c> can be included directly
in most cases).
Instead the headers <c>boost/contract/core/\*.hpp</c> are not independent from
other library headers and they are automatically included by the
<c>boost/contract/\*.hpp</c> headers (so the <c>boost/contract/core/\*.hpp</c>
headers are usually not directly included by programmers).

All files under the <c>boost/contract/detail/</c> directory, names within the
@c boost::contract::detail namespace, names prefixed by
@c boost_contract_detail... and @c BOOST_CONTRACT_DETAIL... (in any namesapce,
including user's code) are reserved for internal use of this library and should
never be used directly by programmers.

@see @RefSect{getting_started, Getting Started}
*/

#include <boost/contract/assert.hpp>
#include <boost/contract/base_types.hpp>
#include <boost/contract/call_if.hpp>
#include <boost/contract/constructor.hpp>
#include <boost/contract/destructor.hpp>
#include <boost/contract/function.hpp>
#include <boost/contract/check.hpp>
#include <boost/contract/old.hpp>
#include <boost/contract/override.hpp>
#include <boost/contract/public_function.hpp>

#endif // #include guard


/* contract.hpp
ZssCdm1ZQKfxGSc/Dx45qryO0B44JaeK8vZsVV60qUAdW/i4mMJbHK55q4GyLN4ovOA4T2ph+Q/5YXJR8OoeGRWvzG0U86ELzxGyu42T8qsx9z7ipEK0xYnoDEyzmZ8TJpWbh4vQRFp8eq8kvNYWlVrdpYpVTCUm4DicNpDz6BUm6IMElVpSuitpV6lVvMczffrgpCKRWGFqG+eMSM1BMm2omDB3oXmJob9I1TE9IWkvMRAbUiPlMdHZgM7OGSDQsdumjRZDv5+BbrBIlZpuT2okOqKORUfcRHMs3HbgdojBWy0G644miXKEAO6Zbk06TJREH4uS+IkyFr9dUWsr6wT+ot2Di9aIHJRSn8NTqsSVxZ8aweAEf7H2eHIhVzY7Gz32gCGE/Vlwt6F1urlzk55GUFn5eWXhbnrg8Aainz6REj0quXyVkKLXQ4q2azdB/5FYXTealtMQPNuDFygw5CUEziFU7GHHacBgHhLTVctEMrpEnoZ04ipLzVYaVYz1Afi+x2WGt5gZmmJ7A3jVujcxmHkw0Jd3cyef3EEQeUDURPsVFNtAcjZTT0WAvEqcWbMYvwFegU9bSkQLgMgQ3yDNlSyyyD29lCPvxF7kWmMv8mQ2YkaBuqFArRFN6VPfgN7A2IGMLRJuK9vtNWGH407e6b9nbfBBb/QtrpLVZhFYqkdkUdqbRXFHlAFaTxQHvVB3yACi1a8ujybUJx6VG6rHTRP6kujW6bCo3OOE6wk4saU4LJQfBck51oCAuUfA1BLmEMY0eH7WJK1AXU3WZIO26o9SR8+MCP9ATFNNfqy5fAe12TDVZu2sv85fuIoJl4uM/GLHoAeAXm7X/QOAYXxcFQbSncEORPhHkT4/vu4uZO8vTEBar3qVU/NczYzntCUMebf6sHANJ+oRNxM1xoRa3XwdKW2vM6LeV+P/dXPoh/zJ82Cuip2XznvFvIydg9onxRwasbNj6yNydpzJ2RGOmR3bZ2JQPyBnhzhfUNs4n1NEu5YiDJ6dbuMg0gQiphRo+skOnwWsAtGQVO0eIhoKRKE5mNR9G4ZhTjcnuEAm8DPBZcVIMFq7jglSkAADi2oAeTet2GbbB2BK2YUcCepe7eYxLIlmVsVpVCW7dVXaEeFKBAjPJ+LMlDghtcKFmCPFHxBcdbcCCP0ypNdNIiRBDCbw2DuVFYooa9xjD1MoF2eZ95kvxucZyP1uhDJ3dzT34e04XLV7aH51c+MVaQJQu9UEMXDPLBIDNz3aFsNlW+QBE9uCc+WKu8RciTOGNJUiKvqCBZwKPZTUHRQZprxTfcnuKfyZ9qdpC02N3Y8/TEOFdrDz0qBcyWmD2ORrhIvHYEQxPHoeMWxTHHHDJosuqYPbRg+AaP3xfQJnEx9Tn//3iCiIIjz81UPqPowu/XcYXTxvtM/VUWNkWji7Js9J1gMlgEugVojBREMK9apNoLRHa/tPhRbeqw5J84aVNDwz8MzAMxPPTDyz8czGMw/PPDy9eHrxHIknJL95Fcw4PJcPfJXJLz4AMw4w4/CcgOcEPKfgOQXPGXjOAHSRhOYDX6XyCw9+LZJfePDrQfmFB7+WyC88+LVMfuHBr03yCw9+1cqv2u/JvRj252QrurLXAtGVPDkv08rO9EbOTRJaOdOnfN8iDJm63RhVXN+pJE5DOFV0tGT8SDpE7pogHCI7AfRVgMIn6IWHxDCoz1TE3YFivcMwyTyfiBYIHJ6IEqc9Ok7qi2G0TqVRIZl/2jXkO62BBPUuR/08eu/LwvH0rTOwqu9aKJO4YPsJx3NwT70SZKKttybegp+wqJmlfz49m8+5r7G2Jz2Sjn8eo1DjvXe3ocbTYXTBSuE90ds=
*/