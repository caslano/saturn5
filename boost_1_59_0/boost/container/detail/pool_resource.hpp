//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_POOL_RESOURCE_HPP
#define BOOST_CONTAINER_POOL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/block_list.hpp>
#include <boost/container/pmr/pool_options.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

class pool_data_t;

static const std::size_t pool_options_minimum_max_blocks_per_chunk = 1u;
static const std::size_t pool_options_default_max_blocks_per_chunk = 32u;
static const std::size_t pool_options_minimum_largest_required_pool_block =
   memory_resource::max_align > 2*sizeof(void*) ? memory_resource::max_align : 2*sizeof(void*);
static const std::size_t pool_options_default_largest_required_pool_block =
   pool_options_minimum_largest_required_pool_block > 4096u
      ? pool_options_minimum_largest_required_pool_block : 4096u;

#endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

class pool_resource
{
   typedef block_list_base<> block_list_base_t;

   pool_options m_options;
   memory_resource&   m_upstream;
   block_list_base_t  m_oversized_list;
   pool_data_t *m_pool_data;
   std::size_t  m_pool_count;

   static void priv_limit_option(std::size_t &val, std::size_t min, std::size_t max);
   static std::size_t priv_pool_index(std::size_t block_size);
   static std::size_t priv_pool_block(std::size_t index);

   void priv_fix_options();
   void priv_init_pools();
   void priv_constructor_body();

   public:

   //! <b>Requires</b>: `upstream` is the address of a valid memory resource.
   //!
   //! <b>Effects</b>: Constructs a pool resource object that will obtain memory
   //!   from upstream whenever the pool resource is unable to satisfy a memory
   //!   request from its own internal data structures. The resulting object will hold
   //!   a copy of upstream, but will not own the resource to which upstream points.
   //!   [ Note: The intention is that calls to upstream->allocate() will be
   //!   substantially fewer than calls to this->allocate() in most cases. - end note 
   //!   The behavior of the pooling mechanism is tuned according to the value of
   //!   the opts argument.
   //!
   //! <b>Throws</b>: Nothing unless upstream->allocate() throws. It is unspecified if
   //!   or under what conditions this constructor calls upstream->allocate().
   pool_resource(const pool_options& opts, memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(pool_options(), get_default_resource())`.
   pool_resource() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(pool_options(), upstream)`.
   explicit pool_resource(memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(opts, get_default_resource())`.
   explicit pool_resource(const pool_options& opts) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   pool_resource(const pool_resource&) = delete;
   pool_resource operator=(const pool_resource&) = delete;
   #else
   private:
   pool_resource          (const pool_resource&);
   pool_resource operator=(const pool_resource&);
   public:
   #endif

   //! <b>Effects</b>: Calls
   //!   `this->release()`.
   ~pool_resource();

   //! <b>Effects</b>: Calls Calls `upstream_resource()->deallocate()` as necessary
   //!   to release all allocated memory. [ Note: memory is released back to
   //!   `upstream_resource()` even if deallocate has not been called for some
   //!   of the allocated blocks. - end note ]
   void release();

   //! <b>Returns</b>: The value of the upstream argument provided to the
   //!   constructor of this object.
   memory_resource* upstream_resource() const;

   //! <b>Returns</b>: The options that control the pooling behavior of this resource.
   //!   The values in the returned struct may differ from those supplied to the pool
   //!   resource constructor in that values of zero will be replaced with
   //!   implementation-defined defaults and sizes may be rounded to unspecified granularity.
   pool_options options() const;

   public:  //public so that [un]synchronized_pool_resource can use them

   //! <b>Returns</b>: A pointer to allocated storage with a size of at least `bytes`.
   //!   The size and alignment of the allocated memory shall meet the requirements for
   //!   a class derived from `memory_resource`.
   //!
   //! <b>Effects</b>: If the pool selected for a block of size bytes is unable to
   //!   satisfy the memory request from its own internal data structures, it will call
   //!   `upstream_resource()->allocate()` to obtain more memory. If `bytes` is larger
   //!   than that which the largest pool can handle, then memory will be allocated
   //!   using `upstream_resource()->allocate()`.
   //!
   //! <b>Throws</b>: Nothing unless `upstream_resource()->allocate()` throws.
   void* do_allocate(std::size_t bytes, std::size_t alignment);

   //! <b>Effects</b>: Return the memory at p to the pool. It is unspecified if or under
   //!   what circumstances this operation will result in a call to
   //!   `upstream_resource()->deallocate()`.
   //!
   //! <b>Throws</b>: Nothing.
   void do_deallocate(void* p, std::size_t bytes, std::size_t alignment);

   //Non-standard observers
   public:
   //! <b>Returns</b>: The number of pools that will be used in the pool resource.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_count() const;

   //! <b>Returns</b>: The index of the pool that will be used to serve the allocation of `bytes`.
   //!   from the pool specified by `pool_index`. Returns `pool_count()` if `bytes` is bigger
   //!   than `options().largest_required_pool_block` (no pool will be used to serve this).
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_index(std::size_t bytes) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number blocks that will be allocated in the next chunk
   //!   from the pool specified by `pool_idx`.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_next_blocks_per_chunk(std::size_t pool_idx) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number of bytes of the block that the specified `pool_idx` pool manages.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_block(std::size_t pool_idx) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number of blocks that the specified `pool_idx` pool has cached
   //!   and will be served without calling the upstream_allocator.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_cached_blocks(std::size_t pool_idx) const;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_POOL_RESOURCE_HPP

/* pool_resource.hpp
+b23RvjPfcs35v/eFObfFkveGlk/Hw/e7gdBIeZBIKRAwzPBw6XeKTvepNDAJeDBx/DAxwZBLRdAqAbfKzPBfaEhk1M+nllVc/sQgFs25+tPOtcSpmpDCHZuaYDq+q/jBGOnVXt1AjuT7BM1grZjaYuCNY7apLtLaLqHMYHz/MCs8p/rFkD8FYUUSa6M2vxGHMJUy8PIWLVKi4N/LGCmOVrGPOFkGJbHv8DQhDBTaQskkXFS16/iORCA6pEVcw0VKCX1YP9TGbVRGH9+plgrKOHQRsOp7gRc/yLsOsooOREXuSDWh4TJmgBfEKE0TOaugsrcjiFmAof7L47MkXMIx1AO+8ioM8EwNjMKSiuGhxenndxkhnz8wBPB29Xa/S66IxS5m5L0Rhjr+c3acw/JZQGnuxzRwwUHTgy7mw5NBiQ6nXmfRDVSAyZyh7G1Um5PgPVFfRPsUilQjFPwFyIicz/WJwkEZ9ehYmn4Jz9c4Zes2wgIEBt43ArcrcVfIm0IGJbuyMcsBvQD0e0/xOus2QAmcdyvZ+ohtVw+fGMtmNxy3n41lR+7izvlNhr/RPMsTzZ1boZLnJlYKw55VmvsPfDsO3gKRSMwAiJy6UTDiOd9hyuL8CH2VREU4DN9NN5ttP4DK19OPKdBRDwUUjoEDJSj6IKMEFZY76Y73y52ytRZGBgEmJkKhdpPuJQEqLvNfvelfXBpOvQSDLtXdvW5JgO6qD4caAGB7XU1rBx61hOzsjVs6gU5GN9wbYkJpLFyd2Y6zb6hnL3mCocTCcsIXlneYsl8R01CWyKuavMv+jqyltoLsDHc5TofMJxDgBq+MGVxcN8xTLwJHxL9Z/hwvYjmZEzgoIe8/FN1W2kQMTyBVzxyenWu4wjA11t8ursuSfoyHgCGORYaEE0sGuPU7VUUCmiD6J6x7oArmE8WEDVESE2BHGfZDVrsTGcELLK0pOB9dz04WNFUkzKGBpCD9N71Moeb2aArkOcnwcdspLeupSCclLmurhD1OXvdSyEUTWscqUq0lJW8h8CugDn+JoP2qSI/jPMH/1Q/ffED0XMWD0RH0maWdOMG48EHUd3HFIR00jMoIeRH0tt3ShpoKLhfiuAInVfUs4khoQU0Mc5vxpT5OQnqL19NAV5Nc8H3U3ChhBJV33rnBCXhAinNBBmrhDBpwk+LeW2BAnw7Bz9J372Kqi8rAwoKmRW8Wg4maTqAWpKZao6A1rXFauODHo784uLgbpJLZXbIWha6apLfJvX16ibMiqan5qNZy/OTuIULlYzo1SsungzH1oaqr8KV1cSN5Qae5oYbxQy0HceOtIX+uoaapgflyIf7BUfW1sLy5QeDncjij4NhxfPxpkjSSaK1+ciynwabrgnGnYn8j8hBlfKApn9qkRNOtOXHqxNz/hNaXOXM1RV6nymzlSng1Spwhip5Boly7ssn7yry5yr4tsuq8ssQ3hFZRcNjdgcMb6xz58vp3orxcPKONOYI2w0sdKymhjTyLqxjJPrqnBhD4c0jz3DuRqwi56XO3kjGVs3JN81nBNlcOD2apXeaqXdcvC9ckXnNX/vDgTeGMG/PUw3PB96GXu8uOGby3aDPDVaFXo/PiYt+5JrmnRsGMi+cLWApwVh8VBqTOBQKBNEcHkH9mWWqOYyW8MnMAAeXLM1muody11VqktydzEO1q7DvNTINn5rt+jKBYCZ8b9MqB9P17c79bwe+JtMJ5wfG3tMz/6YReKfrjQznN2gFz2mJrmgZ7coozWgTn2klG6qD3TKu2quD96oxb2iHbWj4eihJ65u84SgpRmyqw9c+33fiQ22uvqtbIGXiMao79Db1QzZt4TYVLdPJm3P+a+L8W8snqxun59xo59ypzYDMRteXN7hZBBp9YhqfL1qfExqbWD6ngHqjVL6nGp6nyxqnw7MztD01j3czm3c1nw0z4q8z7F8133k6q0/b9N45cnY68iDbtRu48DbbeUbbt2bbY4jb4V/b6lzbZnbba6rb7oi8+FbbNHoxJ7sbXrMbYzye5UyZLIyav8mAYxuM9oNeGsyevKKe5RvrOBSfbbvcZZufsqsf6e9e7RAfZoifec2forwfFu8xIJgfx0cfJpNeJhOfyUdgypufx8QfqLxgJEwfLM5gT6PgxbPgzqOf0dVgzcdg0zufvrmvlcnwmiIwG0wwCfPwP1j4znz4zkIfndBeqfAWSDBtk7DvmrDud/BeojCf/jPN9qOWRSthRiNhhyObhe/iSMdihsRiiTz5bxyoAv9o4UyIPW4HcyKIx/GKQjCLzk81v5+qxf7BWiXLih5el+BxEGYaDe4XHeMZmagaETIb0SIaPUsc+nwVAX8ZXaseEiP6jQ9G3N+vPNZjBt7/vNwLxd2TVkYUh0c0P0QE30dUP0ZQFI/zho5LtI8TV463vN6n3I/HPI7jFpcDh5Yjt5cz/0QYxZXvPIyvu9HquFEwEiTjIICZYUOdACGeAEHNOGH1GGEZGGExMPoss8gkAEfRwDuQQpoxXUvWMQo/MQozAS6Pwj2L8MpccEr1ccASwhs1wKLuMQs78EZF8YxCEWUbvWYbTWZ/WvLKAGZDroUapqcb1I1NxGfNMqSjrptzJOeC96YjVqezw+XtumemkWrLC+jGG2nHA9P5r5xCkqOx8KL3INJdiNOVXdJhedH9M6MLVKHBUKap0KTXZKajgqTJuKQ7d6Hp0KbZMKP7zlR/ulC/y1Z/SNBzTdP7MO0+Sm2/+qzHeKlHuWpHMejGwW+vou5NtO42XKjPnmhL5KxPjO1KdK9PnGzDUa83NOvGiurSfGCUc+7WRH3vnerks6rOsLrGtcrBttrGt9Il0dcVeOuJZa3CuauzvbuXMD+1tT+9frYYiaHcjrmHwzjFaSuHtO+yYMCUh3sLfh6p+RrxHQ0VexUTJnNXGzWdHTnxGN2I//L0Oulo3N41aK0YiIcAiBVvZrttf1Y1gHCA/OGs/8Fof85tvwbZImvczBbbEUvfEurYCiXdEEPYChBcD9DfCPjZCr3cEtza6ifaINzeGvneeh9oikprlnJpD6Jtk0Fvnmxol4ptiHJql9pvHmVsj1pvn2xpH+VqH/RtJw9smK1qlbtulrNonBVuIldqJ19pp+9up//XVIvUPOrRXsvWXlvulq/ukc/t0Ufvrl9mb47jor/STm7s9MZ8MdfxIH/xcJe2gxcdmrD1fKV6NW86nbB5kjB6mrBKWuhFOgV3fu9KF40hEaGTW4yq7GNdr5oWE8XgljPBzRHIDoa3CsuqnRjz1Qx/ADQRdrYkdccSd8ayl8RAcKHudt3WeL0GzkN48LiE/lWle1eVcF6VcValcltl8lA1fVll9Vj1+VCld+cdf+6dfuatfOtt/OA9delt+ej98eCte2eYcG6YcWaocmto8mA4fWlo9Wj4+WCod/cQf/6QfvagfLtweqK+p4btMnu3h60Z7Io8uXnfuLpstbLsdbw8vHFsALWdtfcctsOa/Moq/cKqvco6sMKKdIYV8gZG4BxU4xd07hOU4xO06BLU6iIM0EFI1EOK2EG62Fty10OaOaCfyl1PK9SIgR1g0s4E2q4dNOalZBnbvWCVUzinvHJj73bz9tsIYQfo3/JaOP96oAQwXu51Xum1TufP8xhUeBDkiCrA+rGvtTz4au1/shzERmVaroCMjKR55FJZYqAKooCNZtztBCd9snYIyLOBu5h09lOUc61U/pTksZzk5Bqj85GEfjbuWkUqfLcOdc9J/E03pNVke0U5982ZqJ7c+dUefktqWZFaW7dO8gGa030cZLXyRe6VehAl5wpc0EkmMuvUn8pgXxXqedU8oCqCdG9jjVagenY9+U0tjjmi/aVVGW8f5EvL/MOt8oud4rW2l2qv9/KpnjJWx/dGcca7ea+i8GI09mLE9GGEo/zMyP2s4PHMGPYRwfbbU/IWEfRej/6tIXbvsfPsCvkhcmuH7Prb1Q3km1Kp9QjGKgBIUgSEAEYxRNBfUHK0k/qDvz/4u0lUJdCn000LE0taktTD5FacTowTLvTOj2bgsJGOsw8AsjWbB3xP/rs3GLTsF2WvL0/LMzpfzO4nuhbX/FtAjytFISfJTPt2pGTx9h+9aMmCRk9uqWNKKaTKdcKNlb+oAs2SRvs3Y66m+NNBFy7QrGWG/9G/ag8zxl87RNuQXaLZf7AKSCXp4C7VJjBL+LZVvOu2ryB5I+Le5AVk8UmHembafg4cuZTyT7nuCw1C0wKS4xtb7k49OwGu8JFbCNR06zplTJsbV/JYGoHkHbl83s5+v50QZr//lIbriO+tPkX0e8GETFYl3ahCcF4HkgrI1yII5k6Z7WsG7z/6i8KDjx6cGfV/kITTcvBpQTJ2vgEMzbl3wg/bkkIar+EP5f8hcEz9JkZ38JjcdRJvfpKKoskWSDfgPcrCAiK+o/N5W0XR8H/SGMjmfzy6IdLZY9iADeqVJ5vgGuUdVshk0UWGkJ72Jp3uGIlfDB5v3MKJ8b5B49tGbAVL2KOLr0ASOW5Ro8onBzC4l1kP3aSUjCHbCaXK96kjY1Gg4aiggogcYJwozuAuKxtDT4mPS21qmKg059SZphcg4oz0/lqrp/9sUimtOqGHq93x3tYezsOfuuMgBpJ0rTLI6MnnMva5ZK420Ry+cQle6c2OG4pIvyht0t2hNsYpIr9HzMcRyMYaHyWeWhCrnG8G5g/OBJjIxvMewPv3n/6zrdnhXHEMCJXPu2vDviIYgCie3oG7n51N6lMWnhpJBspJ8b/crpjkBxXkSxYU1HuCsASOQQ4mXJKUDzzWkUpO9B0wmNc6QLkBL9CCMTqkosxzJnsdr6RO6CfsROWu5oUvgWrr58f3DOrGyehDGg4Ihs4voq5Xez1YWJ5VLAQolHBy1O8cYkzO4k+UygZljduCjNSLuOKX2qJ8UqQJna6cBENTqdpF2QNdwV8+dXLZVoWKZprg0nKanGHz8hbnw9p42BSsL2/hvQnWfgT0FmaZtGMaem/v7ycdEHMgEH4tmnOxypTCxJJXyGafT4MDV8Oz+e8/DHxebIAqrWm6et0ZSOcpJKNbMVtcPg2Glm4wgA8PYMaowfvsROtIlm+Du2PCyX4NqrJn8PCPBS/+su8lbCHh46SJU8VbmoH2wc+4OqQai3/Sg8GQtcBbn2ZBvW5VZacFjByWM6wVR5/47vI0C4vE1ipEPN0HYD91WG74FCrT2ZAr2XJx6zVzvRyPW8Sq3J8/jwD5w7l2nCdQJCOXoNI1Uv/8BDVzZKFQznTagQ410MR9s8HST5STPpTBZTFxP5ssVDfIvzDbKnGeDp3HBQVbEN7rgqJKug0YV/cfK3thZhSZbo1u93ZMNIotzWkMHH52WgPejNoXtaASpSt9zMThgqYOTfsmJaxNoijrSfa1mnEftj6E0VzZhyqzmSuYIGft/N+chFmINqAjKADUhCBxv8VfZuMNuwcqanODPkjCOc/yczq4c78o3jxtIIwoRWjrKW3iA5I37TbmY8IkM7x4Jixs79TzoBHXJG23KLG89iI4spyIX7FI1p/maMLBJ3CwL+yrdjJEpdL6k7XJH6VtMRLEC9gQKkVeEwH8n4hugsIlhAk8IwTRDNXSdJPz5MffP6khf/EXeiy+tJRm1DPl5o1XwrcovRLt/1k97clvfedshpbH4S/z372nSRTKGhMFnliAYDZdEGibBZ4EtNiAMSQZ1lJxMjIjPnYFG37XVWCeATP2jEia5+vZ96MorRX0CRQ/Gy9/zfgHB/FYlygrwj3eWCGv4EilRCo5D87+m5Z3UgqFfk5oIKjKi9/D2ILPdNYgZy35HN7YAK6NWoevGGFrXsMunZG5GXbyvgt4gryyXVKI202/whWGKDChPLiirxykZzriAmP1xADI19xR2RCi6jEh55WV1IgFUgJ8VYiEFFm3nogKmJm7WBdyGUxrJZLSGZqoWXkM7QBzIYZ+ZVXKFTs+AR7h6rjbl0knbYYJYOocuztwfOo8YRwAjepBzDGarAMblcAmV65qtq2+tcFrRu/lnihj76LbeOE5tRbfelaf73HO1ilbk4o9532MbYIR2fD813DZg+ubpt0j8fChPtn59bUjE2B/HFQl7CpePA9ca9hZAriyTKa/2Wg6e7XuBlAacrjklWLaaVIH1Gdqf/UYSf95RIsl1Ah7W8j6fQxabxuMrLv03Vw3Aqszmi7QUBZ2eldJvN3BCGmtkMeAapU59UGFyUoHziuxzad7PxOuuZCSQjvOl7DSn74DkxZiN8+H6Ww1hVM1ThJ5Hc91aOyYWcpZYOae1VIfK7pYwkmZ5ZXlYPAsejKqXv24n5McpHx8VHTSRPGmA/cACkZdvwJjNauCV8ADXSnjo+a83wAALP/T/VQTG6Jt/2N8YdCt/NwRsjDrX69NRQ4JoiPFqhKZgaREztgFKwXrTWYBNvbofTil9JeR359EY5kKYphLzLuOgfrDLP08XKaXQo5lIzo112GVmP12SjDpXyoSp5B9vpszdkRnAu9ioK0eWIMMzWtGnHWwMRW+Yu6qRlfQqa3MvHeas2RbSpNiiDerW6a3p6tkq+ClbrmnYe/IwsLY3LGV0A9eI7hd0paiYLljib90kotKNS0FmfG/nx3GSk5QjqaxuSwDfXQWT/cD3TrdbaZ1NAlXAxIitNCYAwftwmYP/Xb8SgYtbx69W/EdRBklAUxgFv32c1a+tWcPF3iSxZrzJLZZZhCIcI6kTmIelrz6Qkl5Pv89d6ifHoef/czTfobQEyndsreQ7INa719SpYUpIfeMrNfeukqRS88sa2UEkUnZ9Shlye2ZBK/Cr9ht4ofP+AjPpBXIqGC3qcxeC+ny4o3j5RLwrpqBFHbSjrwOZtinUbqdZmkfVPBanKzuW/fXBN/i15h9A3rP8t0dogEV/XpZ3/3iS91BEsjRwGwe/E6AQSMXgeyNSb+EUQ591fqok1f86FPfAASth/6uh3WnlydexTh+5PmssUX/w63Y+v0I+nk2aC569DAz6blROa4A+RhvWcKLLhHBj2tm/2XCTjv1YI+1et8MMzGFOzjM2K39t2qMvHZs06b+2ftqEHZ4ngVysz9S0RUit9vmDJvNRD6ZaVmUuZlb80PXX3bXAUPN/ns+6Gse5i7c8u02xuSBBCq1x++jDmzzDQuF77AbuFm+G+/3WQcQYYaqJ0ojYNjn91HnblgMpee7eBUqT0JrB0Zd8nM5GOo9v/9BdnLa12Tegz4e41ZHRVLu9B9KQEy8HcIzvfE4AlcS0KyODQTiay089OO1xKjmSIoJRrbOsR2+axrZmGDNS6V0pIeBpAFA4DRSCsZYiWYuWPmDHn6LBO3y1Z0dfqr1vfzYSvIozWltqOpsjtMxxa0hiTsW7ApweF4e0KBNLjenkJUCBkRMzoE/1wGMyL4PO5rZLQOBmiH9DCBmDKCC0I0Dkcv3v8knokXNGZZGO4tSgzQegCISgjhLvz0iJGykR5g7uJR23lO2DgPIgp8utEyzTc2O25xYSfYcyJoy81uFaiYdBBPfJeOfIBsOX6ZhCI226+84c4/69HpFUWCuEHPQoBlMDCoQuS0T+rP9lFL4w6SYmpU8kdG8VGAnv+xy2Si8xNhnHeUC
*/