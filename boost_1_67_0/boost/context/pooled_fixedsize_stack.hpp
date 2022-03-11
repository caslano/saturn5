
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_POOLED_pooled_fixedsize_H
#define BOOST_CONTEXT_POOLED_pooled_fixedsize_H

#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <new>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/pool/pool.hpp>

#include <boost/context/detail/config.hpp>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
extern "C" {
#include <sys/mman.h>
#include <stdlib.h>
}
#endif

#if defined(BOOST_USE_VALGRIND)
#include <valgrind/valgrind.h>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if defined(BOOST_CONTEXT_USE_MAP_STACK)
namespace detail {
template< typename traitsT >
struct map_stack_allocator {
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    static char * malloc( const size_type bytes) {
        void * block;
        if ( ::posix_memalign( &block, traitsT::page_size(), bytes) != 0) {
            return 0;
        }
        if ( mmap( block, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_FIXED | MAP_STACK, -1, 0) == MAP_FAILED) {
            std::free( block);
            return 0;
        }
        return reinterpret_cast< char * >( block);
    }
    static void free( char * const block) {
        std::free( block);
    }
};
}
#endif

template< typename traitsT >
class basic_pooled_fixedsize_stack {
private:
    class storage {
    private:
        std::atomic< std::size_t >                                  use_count_;
        std::size_t                                                 stack_size_;
#if defined(BOOST_CONTEXT_USE_MAP_STACK)
        boost::pool< detail::map_stack_allocator< traitsT > >       storage_;
#else
        boost::pool< boost::default_user_allocator_malloc_free >    storage_;
#endif

    public:
        storage( std::size_t stack_size, std::size_t next_size, std::size_t max_size) :
                use_count_( 0),
                stack_size_( stack_size),
                storage_( stack_size, next_size, max_size) {
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= stack_size_) );
        }

        stack_context allocate() {
            void * vp = storage_.malloc();
            if ( ! vp) {
                throw std::bad_alloc();
            }
            stack_context sctx;
            sctx.size = stack_size_;
            sctx.sp = static_cast< char * >( vp) + sctx.size;
#if defined(BOOST_USE_VALGRIND)
            sctx.valgrind_stack_id = VALGRIND_STACK_REGISTER( sctx.sp, vp);
#endif
            return sctx;
        }

        void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
            BOOST_ASSERT( sctx.sp);
            BOOST_ASSERT( traits_type::is_unbounded() || ( traits_type::maximum_size() >= sctx.size) );

#if defined(BOOST_USE_VALGRIND)
            VALGRIND_STACK_DEREGISTER( sctx.valgrind_stack_id);
#endif
            void * vp = static_cast< char * >( sctx.sp) - sctx.size;
            storage_.free( vp);
        }

        friend void intrusive_ptr_add_ref( storage * s) noexcept {
            ++s->use_count_;
        }

        friend void intrusive_ptr_release( storage * s) noexcept {
            if ( 0 == --s->use_count_) {
                delete s;
            }
        }
    };

    intrusive_ptr< storage >    storage_;

public:
    typedef traitsT traits_type;

    basic_pooled_fixedsize_stack( std::size_t stack_size = traits_type::default_size(),
                           std::size_t next_size = 32,
                           std::size_t max_size = 0) BOOST_NOEXCEPT_OR_NOTHROW :
        storage_( new storage( stack_size, next_size, max_size) ) {
    }

    stack_context allocate() {
        return storage_->allocate();
    }

    void deallocate( stack_context & sctx) BOOST_NOEXCEPT_OR_NOTHROW {
        storage_->deallocate( sctx);
    }
};

typedef basic_pooled_fixedsize_stack< stack_traits >  pooled_fixedsize_stack;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_POOLED_pooled_fixedsize_H

/* pooled_fixedsize_stack.hpp
ik4Ez2Hd5ivbsl4Yw15Pr2PbfACLmYNXI/4jbIm2RCRoU7JPmd7QboLGqgOayD5yECi2rofxbhLfL3HfBG6RQqbSUNmDZ/E5jgzGHcZqYqnXpqyAci64SqAtqEAwF56kY6vXbv373p8I36jH8kCMaBWFiOUSI1vFAJ8KH0+4/3x+4wLlzH2Seg25yeNKecA9VutQsENGfqedqcgU/AHvKHVF8pwrPEIlZPA9yGB58DwKDr3WUkJUOXwC5guWzKlJyb/hePsGR0emnrnQlfCpYKpdcm/d5TJBOWx+3yYI8sGgUkSop3ylDGjKEr1QtaH/F606M4ojZmGVAnWDI/6SKty2pH++cHTA9JGUanM35AUIS/pMhQcKtI8WElqrI8+iupj/nJFeEwVlUtt5lDT1e6U/ZpXDUG4rJ99QX3I5WxTTl7YxQ73Nkx2RPlPeebxB92zSVH/7fdAfXYO/bvofi1GescpSgrJnKAoL88MPgvLVOuk0ipGyAly4FBenwocZ6vD+PBWg4WMuZ9FAOViL6nygII9wRHnnRss5SwvHqrpxplJqQQXLapi7o2hsowYqIftyspvpQ9f9aq20/XwGQxO7sXVcDhKsRWbGIHL6B4l7D3tIX5kq1IcOoSKN7xF1I/mJ1VAiZDU4ZitARaB2Z/nud8zzIo2SbWGzucuwOvQxQ6QruOmHK9bAjhDfy6kY+PCa/QT+x2LsFgZwVY6Wh23NR/abWjbaieHiKDhOvyKujU5wNbMMuqCsCRrKg+K13KdN2f4sqzeVPhW5yilKryjZvq9zs63tDVJT7YFnsguAixfkjA2SF3Da8sMxBarQJIJETydLr16IudCXgROqCAPLbe4p1OYUs6ngJ1MHwF013h6wQWxjPU9KfNyet2NYj6rR7FcyD8ODZc8GPfIucGBek3Nbr5GCAkUnK7nWyjJCckOtv6u+yg5oJR58tRoaQLG37t3MNmZzY1m5WBZkKChKEleOM04x0Vu0QPzY/AlUQ/JnKS60xCSILvYFO0A4+hMpqSwbzCUEhrM4zsErIkFn0iwU/itAF5vvQmno0mGpHqKLC7hiU4GtVjwYxzvyN2JEyt+Kvcsjo8CEjOjEL9e7aMQ4UJUM6AWe7IHU3WkoJicDN6xJPnpEaQgEPGURHE5jhcdjPVVIMVrt0gb9lbrR5MsLCnW6FuTK4231KStMjaj46WxTuNN5WyCisA6oMw0CXScZbD6tggFg6+1YLtRpXScjIjmTuJAbnNVefOehQZCHV94vAknu+++xB3ZhH34uWHl5U6gINXGiw/R1LISN44X2ahQmOAON+HWM0L3Fh18g3+spdLwv843VRSMVodqGwbUmMvDXXGjS9F02LmSs8eE21i0S3QSqtKNk5dI5mSG/wcEgwIezoo/Rw4VlqBrT9jgnEK4/uNdqId0/JSOGXtdLJD9wVOjf12/bhc+gmRttOBZ1JrWMg4XVTTnxwa+Ek5qJSA5hVqO90AJvF85FwDYCaOY1+6hHkUVa0IUE7Bc8pxK/vbkMCICmIKX17HEyAqGgkvHkyRcd+4Ce1u3zDaoas2Hxn5faqoPjwQK/iTDD2BC0JcJJML3ChDHlS8knRSTM6dO6IbACE/Sa6NjtfvXi8hNYGTSykw4/gMfApLJUWo+omdQKRyIzm7yJ/zQ9QAnJJ8xRjhGf0uM4WZdan/HQ1OuwoF9xrYMp45gDlX52rBnBtYnNVYHhF5jkYvTSR5Z2kKQhlE4TRFEhrdP9vNqD/+0b3oPa6lxaa39NS27Zm2dbMJEIaHaHcCn8zu6meFizYsnrYXo4s2p3eD6fZLx6OFlZ/HygZcnrDp0uqcHePfOatkaoEf4lmm41uXHj6yghGI2fngnrsmsJzf9C74A9cjzQQ/0vle7IHnpdndQjfWIHqugpdpoWwb6cVOFsmWibd7crQbB2Uxd38JWN8gv9URKLHh3odfvogRMik13Daz94qHbGJr+QR5sOdHt26ZpOwZluwqfkl7WXcpoKdq3PST6+PgcyiQ39BfhSE9ZGzr1QpeDrtims2YdNOmajofMpTfcSPMhawJDSuTeOiksQCSkb2KTZkyqt4b5itx7zKTfbvYNGShTHiUL4GDMn7Co9GO6uYjkWg0ZuKo9QAf17jATYu1tI4SyEYgirSAEZkgVS4LgRPeQs6+xexZiwrqg808myNPWUbBZ+wb8xeP8A7z+mh2Dun/mI6SCZTzcYbENi3Z7SN7CExpJTQnmQ/G+VKovcqyNYvpsTFwbqSvEMBWOwwYH7xvMwDIaRzl3NuNS/n9oT8Jvu589ohtJjSZYNuPDKSX8HJAnGiFogsbctOxlAmHsyzGAHeAilbjgHzMU8sW9lsGmuP1XDFiaNoqQlg2HaC3LfeJfoXigDh6jHDhx5o8obFGUWXectidvwBB1BeW0IIQ8HIDfYe9YxQfOes34kx8WD/xh5mvwuofCbxiwOyeklx4SRQDSmAhlcli5IgeFj94EXbyHtQALlSJ9/ks5/Eh62U7HYYFXX0cgNd0LNRZ9PEChS2Dn2B2Mwfjfmk/PqrXGqheR68eYWDGeXNY9NW65eylmBWHUzJKD5kNbhyucVcQtmlbnjZ4OCJpRllEVS72bNpAl8o4WEy5DuQh1K1inhz1rRUkEMWEWkZhMIvh3CV6joTFCRb2PI2Wmvh3n7vSWy5bpMxCi13TvUpMmoMWGqjabnr/ze8fu3GV2VA1KRM73mM9M/yYlba0no7BF7TR+EI4q4a75uujFwl1LH2lOF9JKi1kadoJpZcKTFhkA+LI0DiGiNUOJMwM9DQ2nJ8GhhhYI2knDarerTog4xwSzAtKpiwnJwUMttgiq8AVy2Qh5vVD3l1kiVIQnmDMM2aKXH7Jf2x0ZCkQigf4gNJHGehoFT9GMgh8NKDP8inWcBI3swzlIzuNMwqbpYCxRwEiuOCEYSz3mrg/Bq/4a0GCw0noJP7Ry/4EPqKIVq6sfX1o0cmjC4c+smQCGYlwt1Y0uE7++JrcE0JsXiUb5HxmWxFXX3d59D0tKFw6CnE97G/acJC+R0fJ/MSnsrx4o5uJzQQXoj0MkX+uWO9nFG9fygPTDu2hHO+Gdo2Sd5e0gtVL16vp7pFEKJd2wZ8ZpbhvaV7rt5lNV7vjcSIURvl3/bVh169gZ32/dCFG6P0W/qpbQdc5hophvdgT+KoAJEzztrZMgHPH1n2zbpF4HZhlz2QwpLdQpxmlTlOWltT9yKFFmtKpt7DKz1XFs4n5KiK1gL07EKlH7nSCNWYZniFsYC7D5wC130CFGuNjh54QtOcq0C7OMgFPUIJCpnbSqepPwxlHUFCaiumi6diTu6brICJgwzg73kPtnhBjBJYBZqE8vEGZzhLBsCCH5tB7DPqyfBIpzqkipQweRvGtqiM7NhS+vx8+AM0R2RuVZBTVQF4/LQKvJQtl1o7m15VNA+BRQU5fJAy9f2uASgh76a9aP5og4mH4QWyGcN87ficBkTVkq+SzjzpNn7omBhVhkkuDWNI71rjtEbD6VhDxRki/TBjZh2T3EiHhpS1cGoFhPL5QawuSn25oMN7scWkWwBYBX0VCAts/LrrNJwVQzaDSPQsy1eyFjy+I41Flvkk45/VIcKnyXOPnnmf+7jNC4ItnDVzlRTBRTibZZ6iRnrN6eTJBT5/Pqlt69kqlvEmdq3CUADLslOnJBjnLU6JC314o3wOnSVIDySMYyEULCSi9v8Vm9G7lx3PAWPRGYGaH7fHNAn8Q92IjJrPBp1owxfe3APX/8ZuPb6Gb72JSqGz31aYn3dqAPBF9F4XHq0Iuy/FNHwgepAZD4X4fSBakFkvhaS9dzN8zrPwLdrCwqk5LOfuDTFLcFkPR9a7cKqQHRaVhd+mmRBzCJrOBgxwa+5t+iJcxqIfHZPS2X4MPvIa8QLcciwQexIx7wfjm25w/fGWij179QSD+r+ogS6sV8TrrKh3LRtKZic4/fYjlnPertkyzjDeBzvdKYC6tdXdBcoHUaTbLbcbIQv/GRgYLT0MNH4Li/C3cruFIhjL6G0kxc6SxQTfTabCoJDE/OeLW+JXWiRiK/i6VvAao5nU+EsVhuYpXo6tqFk0q2d/rACk5sFOeugetAXXDnm6mR6FZB/Iwtok3UgSPuTSEFOJVkbZh1duNm4arXaUrnVLfZegPvZjes9vss5s7L6Lf+YYFIAMnqDtaMFvVKa2ZIqmKeD9Rhx7QRsi3RHx6/txxm3bDczs/1MOsNPKPLtDebhi3DZWEjl0wieTWs8CQfX0BlJYJgxDn4MivrPjUlnVkNERZ4J4zvtySe5B7TQ+y1Q3zBDQkoT6TGwb841q0p1OYoDU1xtNuQ+a+AqqtzDaY7e/XI6stvhzVUXZE51C1odE6HeGlc4J8zlz6ZoFtN3d6yUYj4afHBPrXv68E6/TfZ2yov46Wj2XvdkTLWZVa+IFpnbn04P5U1zD1AJY3Yl3y7aTYoOvfzyduCeAMNG/8K+6UgVN+66wjgf0/Y5Kc9/kpiOWUVuX+TcdYZQ6D7eO/rljANX7FHrfKsmYbjePLV/je3IGJzB80JKifOwiFftTMGWCUF/z+BwASnc/RinWjNE27hCpiSdMrGvIcBEiSbyB86KXLf/xW2GYE3rNQtjmbQdwLsyIBX4Z1ofBQ6DE4gDq5Ur0EggtAKR6I261LetKKOctM8Dl7824m4TbNBIdmYDgdZLHyi4bBzx00JETABvbYKLOxbacP08TF/6WRQw7/ilgeJiIkyvdc7rEDa4uCY74z8VqXWrTIf8XY2BT649ETPBXyCKdhRMBWlzwDCRl2wi3+c68KQfX05MSUPbaojFLrtgk2wtlMess9ps8N4QOBiEjKD8vXsmpaHGR3oqTGg5mdf6HtiNe6RPsnNOjkNmjW6tIJGCCfdkHSTXPM9dyO7jLUc1PUFJyDKIaWPaWyAWNhQAsaKYO36GZi2oUkGh7xJf9MMqanPsCw1dIPAh0s5AO4YbWF/MltzpinogPfAlVHO0pF2wzab7rXxjCSrja+202K458RXkZTMUo3lX+Kffm/Hk7lKsojz35anp5xSmv+4zYIly9Qmx8dtxn6ymYPqKH5WnU2MUFEm93YxwmsWp4W5fG1GWs3dqAeGpR62ZmOj8zPjJRSbVM8z5bB7YW8rtiQaHpzRhhEOqHTmiGS/ZPSU185FwrsAUP5/FYojnHr47TX64IiTlLmj+73KN1vf0l1BCS5lkDpbdAAlcF5G9A82YJXHRFz3V0ez5bll01O3jQVR9l5+mqTnj+POahWn9gVEOpRfWRoYwilE20NH905dyCui6YMdfkEWaH/t7uO9Lzu/Hk4PXBvNzv5+7jPubvL48gaCfW7jvBdbXBfPbmdmTy4y7nDw11PQ90j1T3p43r87iFQWHZ5qoePeh/ouNU/MR7g/3otQIoj6fXJ8Byu3RTB0JsT+tE4/EU91FNsotCyLvGxIP5+cvzSeFkN9OiN7L6nMjBK8lCDvSuCbyP2ZubbR9g7kE469eG5o0mcY/KPyp81dGiYZ7cpDpogsH4NOqtSzC+azdz+a3+ndm2w8SmYTTcfgyvu5+aB979PjDV0Opj0hB6EwvQzmwvI5O1Wrwkhse3JnfVRedfaJUuKoWblIcYhJ/Oipqv0hCxQLWDwWY2SxWN2+LCdfDtq6po89uTVpp7VrmdIWwb+GgIVrjFvBz1D8cPmulHA/4aa79CmzyDTV0nfPZSwWtOcaMNVyz7R6Zjj8QbnIvuXL1Cwyl1QhxqwreEZTP/zR9Xd5hm7FoEc7mZpFr37+lcI1CZGXrQ7wh9uN1VTIhyhscs5iglmh2o+bbzRl794wlEDeG3SxJddoJun7uBdjHRJtcRj6xc7CLajK3fNAJEXpoiLYwW++vRkFQdYKtDT4u+jiK/o4YyEnHEHIipCCqOM0HKgKvxbic+GBRR1fc2fKA2dCp97XgvA4I59n1+Xy544Out3N4FPyuQVKhPl0gRjfjn3LYoA0SZQz/3jQmYnbGhfquzhVtmdCN9Mw/oqRKETrpkPMfTD3PpH0PXUgfcB5pc6TqIGlxV1Dpu8gxglT28F+Pczv2o/Uw5J33JsiTIeVO1nRvmW6o/BSbHZwe19TxfSOJGCJGsPuWWVFt61xUETsfwjPpbBTSPIhzOnd4Omm7+uJ6OmG1xzqrCVDSI8bPT+XB1yrgy6BqxZbt9q67hlbX0FNo8dj4XD0caP7RD6ftO5jyzdYb7d5769zLPEpNWujYfA34jaNrIIfz0+AtaOdJ69O1RHpR3mYCrSQD9cLgQ2s4YLLTeAJuQllKRj5GjKFOFuknHZy+IebhQGgjklCTmsf9HPrvJqun++BhlFHfXS9+x8oDXE4vq4v2L1Z0ctAefDyaq8wh3CskLLU8CVK3aVJG+CE6JbRgkhfUqlGOJUKpsQH29nBmgjbpunxnE3pTpTXhX9OrgWuxzRr4eydUVbH8Lh4+K5Kidjhw+RltybdaFAO/biY9Nl7PqDE87uKTjJXQowCTfcyLStLInbcTY8u9txkJ0q3fsUbyZ7Ur7fxqP5T8uvivAealdSt/hCn7E21AVkn9hZqlpan9m2TdYngl2NEyTiYwvWHwVTFmTzEUcDQfISMbpz38ruClTuE5sGPJh3OGxYDZtJnv/+0N1CaiiPjXq1gyPdFlypb2SW0vE+l1FvT+Fb4eW1KbwgG7MTJ+B05Aao1vu8qrb/r8QIstRvpWRkgEW8+z4B3O8+3+l/hujp9bDf/To/PWMJrC4VcmDrbzM8gsZPPDf0YynJ917eiutQxTFtfGOtATjcT4RN+JTBA/7J+LPd3jzfSTXfBpHr/zGldYe+cX5f1TeP1pYB7bof5byHf2ZlgDYTS+7sQL4zPM9xaf1YM8haAvcRhG4m7kbZ6NnYQgXbfxsD+FXypJXwKFun2it+fbGHyELn3CBNVcFZYNaNb+rFBz3uKZvf/q7SxN7ecffOX9TSEf7iD1qqJfPmihRUUfoz43lXDoYp3mq7fSD7q0ueuZZ+0xwwyuYg/WjdUB2B76rxOaXUKOw3QzP5NodVZcc4dd+i9mb41e4eLNRfgoP4da6bjmNTl4oGKsbUcpoizvTenMSqzXKTcDS42Gzf0M2p/hmk9wtU9d2AEt8rO3Nc7Y50LD70P2N22CU5mP9ByInjYwtO1gNz8HXZ5kanpZKSGdO23J8DYTxiiMQ7QTMaXkbHCM4/uQnr5HvbhYii6ozFDworaPSsN7vm0VBAE+vrFruJYEca05sbRwC0qfWGNvPIhimL+vnz7J92mK17X9NjoBpuO1xXN6UMnRP7jLJNL5kGaKJlbOTF+gjvS3OsKeWbNDCKCj+aAXkPwCbHQm/PVLhvX+fkMlVT6MfXSYeYIwd2w9ioQ6iG7CQFPePnm8w6E93XFuyM5LUVGcfoNijtpYSXT77QV0OV3z5OO+EuMlqOlQH7Ub2v1L5mW1ely/4Jli3IggfvXS0d7hKKam3YmDduAt/zl2w1Fw1gkiGsKVAkWcD3VuLWZwwHb/1zwKgyCDF28up5OMRs2wO68q0hLtJg4FgsFYuafrZI7hvnJCOWi3MNAsG+hlsAyPYmalYVwKHqdqf9RXPkDKtE82SYeBvxwiAD824+rDTcxbyR8StqlgjF0zD+/AkKLR1uAJjWxBmlPPiS6SWCGlowChmDchk47HjiUgnbbeOl3Ov8SHXIawmucbwO3pe7xhCTfiJB75S2sjYPW3qi3Dn+u/nf9udRLVBtFlReWaPe62Vl6h3yDVUPVijbOm325AI0nPTVAlQjAU9Yhivx+cUXRYBJoROzRbvJ2JSUOvRNG+TFpH75MOxSczsC2CkueHI6UZ0E4yG1HB7/LTttdSzJc+ReZSTyAeI9PcF3Uq6GWUr2EjQF3+ec5lHQWeVkWwFcRMfo3XwRXaRG23fYi822PbIDKxvOGK1moFjERF1whEfoj9cl/X9WceSiGFmzJdybO/R28Uce3NuQFpAB0WFcJg4eEoqG0T/i6hcEdLS87Pu7Uh+TKWdGr4Ezh443EAfxJbDoGo1jx1H0vwaHCLcGScbfeXMrBJPFlix9Nzdm7ljwrvYFY19zqaaGlW/UTjVj+DV3TH6CqzJdppMosXc8Xyo+nHMh28/4ny6ZIu6p7/7DkQ6WSB0wvCIFksQUe4B8cVFtYkcOFrv9XOr823l7UWbNm994IgpvSChn+QLKXQ2nt8+9XRV5qFlTa16TCbxx2vbZDkK8AQXGwOC5w3WM8BfjoaRO5z4JrNXRGOa9QQvx2k7CCkoM/ZAAYs+dMGEnpeMxm7kw1cgdU94eGOlf80IBJLyx48+qNkKXMyG8/OIsPshwQwqUGSsUk2jaT78WwoR/PHEBgZoeD9PU/LCkzGPBsD4jgzjAVRuplwtAsaph5UIq8qlnFDKXKDZPuZ9YQ1+zCTszZsp6j95f9epRPS2xbEENBZbbBpDAa7WjjXX7gGAmyfVX6uSLRKDaylYhBdbeNsMrciIgh0sGR5tL0k+FccQyAJ7ASGiU55ktrkAGYoOexfy+8GEWQe976ggny1lG8gz0ic8J7hoEKh5BX7UfwtrFN4Ut52mYWI8lRpVNBzPUQQv79tmH+HGTtW1PN2NsB7enZ8O1Cr21uo75FUembKBgpA9P5874UK56MJuAV45J32726Ag/jL+1lU/PD3r/DfCupqq9PoffKHStU8JxJcSrMLV64KszZDsPMYFGK8F5hx9OpnZcwcqup3OlDrBcLExOsTuH0B6fsVUjL7AJvA0yEJxJjdyti+DuJ1B7WjmXF3cwjkMPqEEYzkD1h7qubALtQ8xuBT9pp3T/nKnD4O1JVo/xbw5o78+myemz+XvI4byY3n+nJvJCQUOKOP0OeHYZyJRXtz9qzslzeXqDuRqLuJMxJo7Gj3LK4Y6Yf4LZCHN0SAf3zyd+DTe/o6PKerK+n9ASpvB0gbLVrpM4JXmV4Vv11JgfBXoasevtaRqbxI2xILTfxm000D3M49cM6ytZAogXeHxMaXqSN5EeRZnRYEvJKVKRRu9RpY5WEiRBJ4qdFyUj1vUrTvlBeqHV6k2VE0EZXgOv6zlib8YunWmy07cMprOqJ58WvPPiFj1kwfgoiiAft88Ii5Na85MzP9iPW/pvvX8RRNeRRXw6w=
*/