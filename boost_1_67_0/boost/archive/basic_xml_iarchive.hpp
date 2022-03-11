#ifndef BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_xml_iarchive - read serialized objects from a input text stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_xml_iarchive :
    public detail::common_iarchive<Archive>
{
    unsigned int depth;
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
#endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_start(const char *name);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_end(const char *name);

    // Anything not an attribute and not a name-value pair is an
    // should be trapped here.
    template<class T>
    void load_override(T & t)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t);
    }

    // Anything not an attribute - see below - should be a name value
    // pair and be processed here
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(
        const boost::serialization::nvp< T > & t
    ){
        this->This()->load_start(t.name());
        this->detail_common_iarchive::load_override(t.value());
        this->This()->load_end(t.name());
    }

    // specific overrides for attributes - handle as
    // primitives. These are not name-value pairs
    // so they have to be intercepted here and passed on to load.
    // although the class_id is included in the xml text file in order
    // to make the file self describing, it isn't used when loading
    // an xml archive.  So we can skip it here.  Note: we MUST override
    // it otherwise it will be loaded as a normal primitive w/o tag and
    // leaving the archive in an undetermined state
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_id_type & t);
    void load_override(class_id_optional_type & /* t */){}
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(object_id_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(version_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(tracking_type & t);
    // class_name_type can't be handled here as it depends upon the
    // char type used by the stream.  So require the derived implementation
    // handle this.
    // void load_override(class_name_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_xml_iarchive(unsigned int flags);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_xml_iarchive();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

/* basic_xml_iarchive.hpp
fu2xfMPoFMmrNhcqwO6tYtICnSBJJNr/b3h5NzIqCaUABifqDLbFUwkB2MUmFFyWikkUxevtAug16v9xAfAPoxQK9ErHFWzIHflHkFDvDlzeSsLbG9yHEIllLB3zbORUsCo3t58sR5dzGDtnTo5uPqpavWXM4NxEzc8Kl8DuuMTrp+DSTtTr2Gxqmf19jXo7j4IsIYuJeyHhnqg803lishWuBNutER/CI4HIQSGAvVEdYW4vxlOZBK1AJYug/H9Lbc1Ot7CSw+XdGt1Fe2Ixx6+9aB4wzg2U0tASavZuo9Fz+XQvRLQq1T5fy3b0cifWPLcmAdT1PTI0G59MJbupgd31Cq9JRe5lhYCZamytnBcuft9+7LOl53KRKEUlrJfCW8hj32OeiUrxBOQEHpGASFZdE54RFoH0cGK0b430c1eh5E1+X9bvjVBX/kVqag5PQTts60l14CSoJtMoN+GCqic5OfBZXykwe+pY1jAu0t752lIdzPH6VlHSTzcCXA6ppwzCBKsV+p6mZc5uY88409vFsvJFeijuH1JVAd0sH9UijvO87TiXkxYpCgVYUIM+K21xQhdEVlSmIs/r/O7xNduM8vnczfwpXVUwWt5HyKf8Ab7GHSxkUt+tdl28WP7AwYFiX84/M6/rc2F7WrwKDL1GDkIhbeMaHn8d6/dSu8SNB1+VfVeReW4e31MjMf63iAegJ/FRJoI8Jse94gwIi2LWofnb7t+3XemMjmQ/FAA17TS7lwS/YhnclnuBODobspOWu4lmniaDt0oMnxajVZfLVaTuMaHAitzzFLT5YZ5+XbfBlYpdIX4NQGOuOFsfNQPgCDyl6GKii+P+I+Z5OgjBQeszgShR/bQkKEFPBLXxRoPhN4waGvG6WvQ/ilnjFnm+/lHMHGydbeYMe7LDjpiWwTltiXhnuawYvvpdaBEvS9BX1nfM+jXAW9PSj7OeZTJgnJylUazwQ5IpAlBILF22vhyAz1P8vfhFwUtENt2+USL3tPHliBEdHFX6RIDC98eVTZbADqJamNobkbN8fE17phLrUSEMzRvKIZu4Ud5jPB2snkioJujgzk3dsxhkMsnQRDcp8q1Kie2+BTa2r2rLhZ6Pq49GuzQJxPVjgmbnjrxY6uA8zSbYdEP2cYvbJWIb9YOLXluCyAcPniURoJA8xcgeoVMRt3oHZcnEKGfRIj7rIKu2VveMP2+f4P1eIcKOcrMHKu5W6v37gYPvldBjx4wo7eVbTqfagl+q/jH5z2U+a61OTq9fCXgSnJq3039pv1Si8Mem3NHBZrocDv/WydnEpBIZ5p8weXhDemBdobo0nSYNOdAhAYHmqXhPooRBA9RC1GQ2fF5jd83G9XBIR29xZ/i7sYbDjskKBklZjE4BeQYyeujbQdvYnAct3RzwyqDzv7QssQ65Os+Q4NY2Z4vwRnZpmFLXZ43qRS8TJ1T4yKyfmKH0cnUQ6u2OgEAilPrJl4P6thBS0aysiB5n/pOL2KyOI3psBtuGknLAx3enhCU3eKPFGD4VD9rhyPbFgXvNiTqS5Za+dsR5mfs8hdKMpc/cTpCpoxSiMzX28ew2FqPhPjqF6EQ13d9SnF26XPU471x2pFUnjDc5NcrzWAg0SA0of/Uuawey6/00V+NyZKUOYDYZTys6eCalyflmMNX5IrqRQYI9XY+GafdT2RLXolfBSt8/k1xUJAnGiJLolhNNepGCv9fDW6dvhUtR+Rr82str0nDnnl4ECGQA4XJQG8kQfkavk2IlZMXnsVX3SZNxL2zC5xn7VHR0J3ykXLCCk+Ncxdo7GzNeObF58W9dSqGsdDNfanmRa+GlvsMgbXJWUJjtotxnUN0iZtPa00nxSFT4qc5qCTpZc1MD4PxmUSNGuCuQBIkAgiBvs1dpaHllKoIpX6tHNoHGQKCv814KRNLfaQIwOjsJ6KDgZWDl7oNcHnJhvHT9d6JoDRIz4B/STUbfO01MeIfDROMEQd6TqfPMM4M3lVYjWRO9ArxUekOlz+ylXr2fHPS6MntAg/RpZShLZ+uIaI71OsiKjZUVc7T+puk4/lYvFT1OjJPwVIhWwPsBLTltWQfDck6TQ1CCXODhYuP+GF4N9WoWWqYA6i27Lif8D3eAcGlEH04ImeWgPCWNp6t6TXR1z2XW1LCVE9v0sfehZzrLLsBR7wnFM0Uexsi4JNTOxDCFS3463b75SZ+hTRJxkWeLE4RW42Dld6VuHO8cjyFRF3OHDqDM5dWPrltZ7avoV4uk6dl78djGIFc9DFYNs9ZS3XNTJ46PMchbeOiVYL4kdrqYD1j0M5jYmMNK8zxftTFSZRdFwEQrooBae2ykSK6awIbP8a1vhuxBKlMarVRYkfcoyjvPBIuBAZepVTtq88PtWU9yOZSuzpF1qYYVya/pj8jlCOFPe1bemeDsNX22MSCQJJMHOtygwfu5zdrn7KsZuJtTyIdy/vEDw/oHCob4O4qoz12wsb4At1l9F+BIbUjDz+n6G9DgTqU1szZUAAyXCcTSbU2KzkVY6CByHE4wsCLOeec+rsgkMkPvV9x2w+tmKeVxMfd+t9+Kfcqkg0pM9BVLzZU8hvZFYAkwPdj5EKE37Un7zA3N81Z25DghFBqrtJQR+daJRjgCHL8jINBQNHnMHfAutdiZWoF1faUt6skWt5mt2O0akqzVQ4aSHab3AdD1GZnzmGMy0WVSzQpdcnLf9wPZ/dZp6fLUwUty1RLXYlS7owGN06jOgZD7B9wepX5SVG8G+35lRE0yQ6wEtXmXekjwEjeeQMfvI6Aa1JcZV4JiY0mZWkCW/WEQfZuTxRMCzvr68Yx4lXq3hRkcVvKPT85HRW0luyhChrM5XPqUg2WynKaEtVpWkPHy2tYG6AZWPJBkPnLmFECd5yQnc+NP6BBw+yT8mm7fUpxAUEH2K1wffVEPJptu3hrXsDlwKTQAl7HasDpgQANSwQmaDciBkkeZ2B0Sd96Prs9QACYxBwY0vSlGTlTwAVyzuXnqZodZe+fhkmdjmt709SLjmq3SGVz2YR3ypZTX3wF69YycTmZxC/wX9DjyvebzEEdl2IHPgun53EOXZrDr1Drb3MnwbXfWTJ+UzY/gB7LlUgYBYKxjCwj2RcMjMPCrohDLNwjAEedcCWRicjnqSZZiZK2GJq0vfzQjwMh1srcjHFYxMDYje+2+dZvtnrkY7DzzeY7VOp8EcTpbJZpGZrYh5vga7gbd46/d8000NwlUrPpPKVL9mfC1bL5935VDQFq6vnEDXAK8FCmGIHFsrSy1mhrolchlQYva1hWzh57263AK2yMAEb0jCeM6aQN2ZjbCLS5urhltHXLqI/gp+G/4xFGJaAtHhA5nR/72Nvdsl6q3zGgelmETNl0+Ma8UacOSRGT2hAvm3tIC081xdNvE1lRyNBuULmY5FXtMFylTax5L3CPHrOfTUOPSbFIzUbDT1PoThqfja9eWREBHC6FvxUcnSHweEYlFPAjEGD6RYMsT65DHGVxE8xmaCsk4AQAQNVP+ugzejgfESX9p626Nl3l6ZbUlikMDv//rqDOPlxt7SiZy5parkYWagrN0t+c/e23BcZvm+q7VnjafeBGZLGXSKOpvOSAPfi1zn55DJxfITnbrBDqcpNMKie3X7GskIJHAQjLAo0UutcZHAKbYPAdbH5kgBqCuykoQdWfYEnDRLBM4/g/QHkXhZitmH4a/p6XW1fubsdScvTRYGBd6Tu8sSqH+PJaFwLwl4tUmqliW7yP1tuxPMD3FYfvQk4zxvG0Sx2fe1CCC1fdL+WuZWWRHNdMrER0j8m15sHM6/SY9sDFCbDZ2ESCRy0EuZe4xgq3RrDIWOOCQ4pvLGgifLYJx2JpECuSOMzCaGYTGCsHIdoa11GUTOL3murLNGs1OcTr7s5v4lj4Nh+5DKG4O90sBb6opU5cwQgALvn/fZoBiYHctRXr/5Eo3tRdRvOc7dhsml5a+F1xYu8Oa2K0Z6mqgoYvQgf12dBdtrK42KkCn6+dPLNWf52jiy4xT2wwDJi5yiz1Fkgpps7PsTOp8oev0Hu8Njl4YSCYI3qtHEedc3zfkycc0/o0hwTloz0pejMvnUrRfQj+mZkz1VGbYKFzEp4pq2W0oGe+J53MKl4CTStDtmWaSo9unvdUAf67baVJZLsRTmULxOU+1VwBYjpdIWA2sdcBBJSuBbHO02UTrKbp7ZrgtUENjEJJJMSaPaq92xwqOLSACRErCg6kciWVyv7FAG2GmqSZxQ9z1VlVZsFyrPT/EjvNQ8S6494M2C6pM7dDFnogm4ZvqhK2Phe9SulWfNFt8y2SV5w9pWssFLeD/VC9xvHBOwaxj/qAW+NX1eaQBhGTTAip2fDqKj7o6dCQD955hitO53dhJTfRrubNU9p7Corni+A8hiYhAk0pwFKiViJ1kgUDYyZj5FD1sCrXipZi5qiZvNqzZqSYAGbSJm/kuHMmNqn7fjFNzpAAq01JgarMOOzkmBD+b620RKg2bFGDPwHtFzbF2v7Vmsu/vUgMY4iqUQsHNJp8pPsu8YdPnx1MRX4AdptSPR5Usz+1+1xk3UKP6uXlm99wvyoaIYhAMPzZF56stS6RU0CXqehPXLdRXtu4nPhOlqbq04tuQjeNcE3J+j2X9qAOA0NYOej5rd/juKJcEV6c8KjNiyll+70hryxoj102EgASmhIu1Lowwm7dQ6GakSSGO1eu2qCwV4VO174nF4xjJ8eIJvP2Hbfbp9bjhDY9u07dbkv6+atze8iSoLRDRDAIekjj077GAI6LpahXWd3vRd6jUAX8LPFeT8McS+tGvTgiXYWFqzW6tvQExLg2jRLUc28tWUmEmmdHzY1YsGaqQUt5VU6ZmYcpbfGFfwyA4ICHtP5kEiJRA7en7O9bvmzagEMvLHUqS2pkCsmGFP8HrOIDJ3D7bCrI4xyVI24JH4KaEsf9upGkEW+BSyj1HhqkLDQTxR2BFqMtDARSNyJirGyUXS2twj3FEKh4QZuAna7RBHQxmCAceMkCfgO3c/l1NQcMNv8/onSOXRYuvlISxkD2MQhm+We2WWTVj7XcdnBd0dpiSBpNSmhu96/6T82F52URvl8BQo0gdI4an/LXIy2RbZQyPT/sKvp3JwT222FyVYbwCPJtVw7NUCac3s+wslmlvfAa7hDHut8Sg2mTgK04yQhJJRDVdOyqmISGrknFhg4PFtalCNQ5o3dgbvL+15KyJFA8CXiJGpqUpd1NN3KjSQKy0uEVjzFGL4m+dDlVNd4tZdmtmclDmLoVZVqEcesHIH8uk8Z2tZork2w4V7p5Gpw08t7lOYjHYrVpjAI+NjFlfe2Z2ihwnuPPOU3ybMm9EoKrx2QLIEwmyIK2qHHGVNSMYk2l4zHYGTyaiMMkFxq+CobK/CbwTR5eDyXO+EmE2M0lkqJSON8i4IGdiQJUNK3+xGEE8Nc8d5OR/izmL7KuJc212ml3TnT3LVUVttMPkkdBhWVbUcp8BXg01lx13LU2ISlTuA6fWsClWVTWOh7X4TylLwVqe+CWR0AicPXFSMwsALJiWHfVl95ujT1d6EHF7mRngw/DlDut9/eDmXBBPd1TCY3ht8X7PqeHQuEeIHd4T73Qg4MPJbiXnzhtqS0tTt5sZa6JvUnZBjlo2S6noiBtvm2eRotnGh5jwqMcyqpYYs8CzPDHo9X0WaTHCMkvdPvBMDQFstRbvN+KSyNKIS0PF8Ugp5T9dss9OIPKphYAWVBI67K3tDaeuVJGpMOHBQvZa6oHwEkYwpxSGUoSJuZ1G014nOYdnEZ1u4C1p2YITOZUW7dQjDyl4LPjedtBWAcpdvwc7k1DKA9wSKHIfRocPoDqVKvHfTDzXIt3qVmVJ6Ox+Z4GGG7NHjYZprMDXvHywOvuG3frjlR/w4fv+8yeKtezrK2J7rsC0rdAqIzhXwWdsYAhcHYDFN7e2fvo5hhzRrgwHxuNtVsOjArU6rJpgKTh/JFSZZbjswe/QwYZcGn+T/pMRKlS8azY1bNbsjuAs6rO9lbsRFjcaJNstbaYCVzbJHC2LSx7EQWOucOmGHHa9nF8rk3rs0bpIbv3fk1EEtkeiloNFvz1FY88d/rslgAxliLwhDpnD81LzDmDDAIm3fSKKHEEV52w2gO6pqQR10wPN6upsWbrbViA4js7iPg6nOPlMFPhZxnM8mDPARtSIlvLilMjWODHnieZsXtWnbsZEPyPrGXem7NECQuo3k6O/NmjHhUsOlSeUerxMOS6EnVVzr3gpvHlScAGBJKo2uI/sepnFOwLSoyEw7C+EYvDsBLi75x5u/x5ttin6wHseLEStmzB1q++kqNNNwYInPgWozerOplz5rvJZFEpjMidKRs68s2Cm7xSFjbNd0jsIFbvkGassZwSV10RMYpKgK5XtKXx3LvVkiRX5hu4zgtbIb8WLoD1PdPBwz2LSbB1/6gB8QVKDSC+u+EBLo77M/LcWbw6q+92gtKex503yLuBIh6EzgmIBBHjgX0io9ER2dw6Wx6vQHQKwcFLsNYZtsaleUVBsejeRkkk1sBBQvOseNiGdZ0V3PracLwWVEjgxwTO1wM9laSWUx/AzVgyGJlPs+Ae7JpA5VEQvC40zTQSH77tXCZ/E2q3pG9eBHRviOtlMpt2aJVD1wY2jF2mbINhqPqHD7urJ+xGR70aMVTJ13dnZXcqhAELgPodgMybysoGBGJgmQYwLnCC5HG602VUNFeI0Ken9tSz5/IMUBzCaHMIAqetvaYZXRe0+NLlKEW8jU9q2XoTDyDgw0qzx3cygtKV5II/PSrtxkSDiugIdF6m5Tf7Sxsbfd1vec6KM9DLob6ty/cdcLpWiUAAlSvQQE7PxS3NZgysr+guq+W7NCzR+087o6NfZFOx4xTYFoXuSBkxSCAQeivDwOmZ51yBfeaQpLeGtO8sB7Se1VHALGSM54ALw47j/3dal55DUSMTxdvwb1O1W/wp2boeYiqnM2PohRE6qua+vHllzw4EPIGlAGrEtPmIl05uaaKHDYWNzP4xSv3tqTX9fDC9Llsq7IM87Ehew78FZBzbcFVdfLz115gG3PD9bf0N5Oe7W3v4Fito3CvdUyx/mPGbeO6R7gnNr1nq/WYPTRrr1f8ytoDC68s5sXQLPQPOJGwZoaDvkW6HFpjamNfymQTy48HL8DuR7B4/DJDbnS8mow+T3aaEeTsqsxPc0Qw4YDOzcbc2uEG1jpEIuqjIhJg5Mtc4bMMh97NqtMXFFpQ/XogPKuLqKPj+y7iwBJoHoylJErSJ4aCz7SLE4Ke/G/8tN0/7psPeybbdttW0ynJ+HbvA0eSnBvxQE9RpJJYB9CUjXQyqRd6887Dr1PpKG3IQjw7DgraHFpmqIJSFDAQZpQh1Zw0Sl6XbjnI0c5FwDq9hpWsqrMvKpmvQBAQc/l067i6L9btw2+QkwkeDLnBsBkSYbo93Jf93b0mo29bYViGKwV4pDYa48dZzWUMsyn+P2pZIIfCVkQ9vjCPGMVsqy/+rjVrjAezkeM/kR73f/KTMyx23kN5YNmxhkGKA15ukei+kywo/+NQ2kgakl6xMxdSuTukgystNVHBOMRhuMyAr8sVW7qWVn5dhHVJvqqeDyLNXe4h7EQB5zoH4nmdedNsuUHy41uppBHRRM4PlaYlveklPYsL0dYj2MIfVC01v60dw8c4wxxaBnVf1Ppw64zXeX/wRdaDdHk8RSCBBLDdpennCAw5g4ZaXVJx3c+QHRfRv8bDVcr0Mp3wd2oQDCY5KJi6DWiT3zXQKqzuQxCFbxBLiGAC8586ioTmLPfILxNW5gEpHOBrJsN8xbcYGdVe0yV2azZrgzZ+yoO0+pcMiGgsgtEdcGHRblZaKjZqQDFLZjI912h+1kSD58sTo/lLu/8lZLo8NSiOa/bbnblFqk2aMflT8OTxhL8x0wzWX/R9FnRMpcp9SHFoiVWS7ALH2f8q81ffEB3ws1JkDYbTh8k8xLRR+Mz61Q3g4ghzzuAcPlloCvwPoFAQhCJNdTbCDcEgDg2rZt21vbtm3btm17a9u2u7Vtu739c5PzJedxkpkMfjrCbxtBCewjVJGOCNBY/MV5ortCAdGaca8gXFebYFC5Q1Qx8kulLHOWulJyZ7dY2PT9TU5AQ/RHG7AN/Rjnj30Xs1CQM0LDhxDW8VMAxfkYdh18lo/ybRPxMNzmAeKm9Bc/KLas3o4kvqsvcNe4m3PjBAkwDNdoHdO3O0iHDdZ+wrDdlX36uuO0Xut2teX9+1diBDICBTvidAw0EcZz1DWhyq0WxIGDCFIAgAkWSghNkLn5sZtSIMXDL2C4sEWKo80KKrutDId3tS2hHOhkca8/mfu5GMTp1y3du8yKGq0tbuReNwldMhBUPNrmk6XJdlYBsKyvVDcc8E1i/ESqsnikqnt8pYLmqzldAkuknwC/mv/luxzT5OGi4fuT9eNV27QiCjB2Ktp9vf3TWG2Ftstpv8H3XiLYc7d4ZT7243Wt2+IqVfjKgWs5iNvQz3Cj7N/SAQSYr05QUlLZh+XfVRBDOp27Ygwxvp/JX3BAqlzbBPWShVUzDF4zzXoEWVcO9wzvKiLzr6m+EZw5FNeqcdOVnnSmId2mFJxRMPCpZg0yHmRKSg7Ft04KPwH38RCNWcd1tPX/azyg0dqD7G7xx2yEo9YwrIxl/E9MPRsy3QOhcnPK+Xrv6WdX/0WY1tU+fTQcdEwOfLJbITdB5E2RCuWW45s4B6tg63Nf09+wAGpnysxoFkWaDqFWU/IWnAdmikTtbuqCA9qx0VYWizC2RMxOg9tlxiQCT92EXr/GiohuRucyuJAuNBUKi0NlWGCEDaxanLiY2S+adDlkuz+k0cPwQLFvoRmDFna0ujn47yqr/MJlQSyIuTqxjkIJ/uy+lamaubZJ54kBLzwPHphvwQIwK0x/0nA9P+QRKJwU7GVf92+t8WKGdjyI5k7b77eDnKbEh1tLP67ozCAj+Ra7NHFMeZDp8ttczttSco4YMIsnbBAFuQzCSCDVk9uMpZVR4tLEbeahDPcTRlGYy/Z33GDUC7LuNvbP0CK0gAOSRdKYXZiCJLkAdXci42pIUinu6rI/p0FWXQEfXPayYzDe6J0ZDYAU7NCFBgqqqpJZcNkeQ6s=
*/