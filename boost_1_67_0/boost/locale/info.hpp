//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_INFO_HPP_INCLUDED
#define BOOST_LOCALE_INFO_HPP_INCLUDED
#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif
#include <locale>
#include <string>


namespace boost {
    namespace locale {

        ///
        /// \brief a facet that holds general information about locale
        ///
        /// This facet should be always created in order to make all Boost.Locale functions work
        ///
        class BOOST_LOCALE_DECL info : public std::locale::facet
        {
        public:
            static std::locale::id id; ///< This member uniquely defines this facet, required by STL 

            ///
            /// String information about the locale
            ///
            enum string_propery {
                language_property,  ///< ISO 639 language id
                country_property,   ///< ISO 3166 country id
                variant_property,   ///< Variant for locale
                encoding_property,   ///< encoding name
                name_property       ///< locale name
            };

            ///
            /// Integer information about locale
            ///
            enum integer_property {
                utf8_property       ///< Non zero value if uses UTF-8 encoding
            };

          
            ///
            /// Standard facet's constructor
            /// 
            info(size_t refs = 0) : std::locale::facet(refs)
            {
            }
            ///
            /// Get language name
            ///
            std::string language() const 
            {
                return get_string_property(language_property);
            }
            ///
            /// Get country name
            ///
            std::string country() const
            {
                return get_string_property(country_property);
            }
            ///
            /// Get locale variant
            ///
            std::string variant() const
            {
                return get_string_property(variant_property);
            }
            ///
            /// Get encoding
            ///
            std::string encoding() const
            {
                return get_string_property(encoding_property);
            }

            ///
            /// Get the name of the locale, like en_US.UTF-8
            ///
            std::string name() const
            {
                return get_string_property(name_property);
            }

            ///
            /// True if the underlying encoding is UTF-8 (for char streams and strings)
            ///
            bool utf8() const
            {
                return get_integer_property(utf8_property) != 0;
            }
            
#if defined (__SUNPRO_CC) && defined (_RWSTD_VER)
            std::locale::id& __get_id (void) const { return id; }
#endif
        protected:
            ///
            /// Get string property by its id \a v
            ///
            virtual std::string get_string_property(string_propery v) const = 0;
            ///
            /// Get integer property by its id \a v
            ///
            virtual int get_integer_property(integer_property v) const = 0;
        };

    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* info.hpp
Fb1ZvxnG/c94T/rVYbVCTMvSFsWkyCDqUzBEHppDQOciT4VciXmWqnxx/ftopPQbo431OI2P4Oeqbh1R8eAObZQM1wS+/TbwKyvVF1rrznMqnc2Xno9mfnXRWJxGQEcyW5fQiRQxZjsnfrN5hKwsKP+xLbg2tUDLpc9cMIHxSM75kXC5XmMig+MwF3cj1FclWP16ONEXT8zDuVl0pon+NPnzGpBQLnEAZ1jv+hd+4PsnNGtLsrK8tDaCDzAopRxtDhBxopNQgblVN/xK99JnoLvHNSzFgCcDQzJA4rP3yFteNNhpVoYOCeCMEFnL8UwtMKtyfycAGday+2zecSnvct0Gg4mOyWkl84NhTOmiquaNr3Jhx+bxS8yzxZeSyxIn9i6owbnHjM8KZNrbgshnfd1GiKzdflD79jmaW9k7+hyrFM5qDl569OHW+VvuoEq7/+qsbDddqegkF05pJFCHC/vrezOVP0OgPDv3YjDO1QehpJbqqSjO9rmPH0E+SVVR6ObJAO2DEUZDMziOLEMAoRx47FM5RrTo8LjN7FEezlaHxEIh78QdK3hYIU5as4eoaFRdcSeda9wB5c0HkqrdBwc4Oh+O97I7ep9mJ/V3oTPAbKW3qWvS140YsnoO5wFpybUmLzmqWTmGE0RyhHMgnTzOJyGdVeS8qGOG8MPVdubHGlbUJ5r3NFkx2pottFtH+4WhsTQUI/T3S+w/YwjJHS157X7EFrhUU6Gu1w0BD4qZz6uKmgc1Tc5zFeC0jPmiU2MRNwGeMR4ki460pDaPnFx7rNvb1yh9DJNGPJPpcNjO488wlnJ6cD8APyEpQAC/X980s0JOShv1I6Mru43kuYRXBNYMShEm2BKrM4uN+3/KSVOLDpicpQTC2Dn+05rC6PCjV0BaurwCOVpwGpR7iamngYSkWB5ecrLdvrvoKkxEgKHuGkzFe0GFvYaLGLJ3PP/C8vufU+TP4e6vSg6K6NeueOFuZMRVm5S+op44VrbqEUOxeXp2NJfNOeYlZ6BjLdTMc4vOBZM3Jn/XbopclNV6bvf8UFhyrUPlT9a0t2+eYQ/UuRPRjpziCbHiq/YXK5D0fJhcRyGf9vGRyUSYPS5ZCI4fKHZUef69FFjjB19O3bs/+WjWnA869C5lH+9zuUbF7zClt9cQ+1X8/E4FRj13qRuwpDtFByNtWWrhq/Wzirtaj6b3rzXyO5IefL/+it4U5tbKc3qcWpL1eCgCctYCUNadl4/rtaR6WSRiEwIjnNMlxs5VbPR9yp6nNS0csS0kxfUaTapyl9sFULMVRpiHF3Q8XcnSyPZrhDfE0ZwH1MNCQ5yxH3sQRkNgX82/LQqSECV+Xnz/VAPcW7f3Ms0lwA+vsJoIr8uTxhvQ7IE8t2DxDpouPVap7lanUPK9SzXnof56YaxCCj7HdoGvAwi7Cr9KlaIy/ud5HdyC2imnGHsc2FdBevKE4P36fEqJKSGhsD7lcquWS/iEXw5IGJa7lKdxZ7v+TvR13RaU/284zA8NUT0YcEMozoYxS7J86oNp1PMSj67pJWBfsvyki9W7LCZarMFjnvRwI6R2NESbEG956acfX1S+Hen8gXK08c4gwAaQAsDr1ywn4SU07u45nZ/iUTjci/ugTnaaw870DDEMhg8mdQm/O68weMk5sEO0CgaqFTCgzp3laaxTSss3UlNqjO4QzhFcy4WGcMvZd3uRrhHMn1cU+vMQcmiXqpWcIaFX7bTVFdU9L5RvY9z5MELpJ9HeyvErRxPrZlpEJS1ihwbOy6pabCu/Ijc5ltj2X84qrVLdVeXvx+8ZHzzWF+yJE170KkgloWQbbFBvFmdupuZmcyAmbdKivOebVySOWOdtjo9ZlR8CcdHEPUb9xqJM6RRkDOhyabzYRUz71INoDMYXIiX70HYPp4i77GcB7wl0+np2Lzrpo1gewTfq8dvninr17q6EnGDAIxyoneb7e5NIya857L+RXK/lhMDcFrEbnVMRE7CepYNK5PFr0HtX9zR70sjBeqzBefXNeGsAb4KvX/GTQVFMMskZtINsM7ojFrllmIKr0utyw5zJBqIKnsbbwy4VVQJbGv1rlfyHNSw8WfOGD7fmE4GM/0SZFZ7jLlIJkRI9nLGUp2k3doORmj6MSUHmkLraXGAegYmpj/GO2EupJfUfOxVciPCwsV5udOF8i00/dY0oME1n9Vu0SOFlVLJPI8aw8ccxOjlmDXeOL/yJTdEfx9zNmktiQcTpNjbj+Sn/C7cnoQwbwPX58aIiCfc5TpW2nxsMCUa0zNBB7K7fmZGoyED+hRxg84Xq6JncCGctVN/ZAb85aM66FbO3Gz5rfDM5k3F6bveEWGQIhPPHQ0nGDq6Tt8Z7rfk38R3AWq8TOBK7ettA21i8HnVcpdD6DOQV5nb9uh3q9Y75tAEQhVYNkly+MT0tdk82uZmtGomX7usr3aN7JcbUS+mgjKJZVHl6EP9S7LIs4l7fIE09/XKZQfvCz45dnvQmsT+ARmDi76v8TU1vbHba07sR3/xpViuYkEDoNGmAkr5kV3z26OckcmvnDo9Dvpb3IqZNXyqDpSG7dd45G7f+5l18Ym7ffYHUfid/dxzsfFse8jkmae8ziP8Ap7BHWkEGCLrwCc6TBPCq+sBQfOEQMgRMW6TkpFSoRTtrxSmKVUMaLUzrFXRKA154FxFewA8be7o5XsGOl0oapd1g6hve1/9W6MqtSMkJVh5jdKsdgmB8RsyKAB/wa8u4ZFLu1osVVnzu8xOUPQHF6Et8V9PmMdkVKv5ufLkyH3uBW0He1gmBcm1aXaNY52fx5ghI0ufhLqOsHenRHext2kM65gNyxXrsPIChqDasFRUYtxqPu2VaXfHI5AKeVURKd1MolbHLMgjnyjhBPEyTIiPw3fGDYz6wdQ1v5MJmYY0aHWVzBxwLsAsvGf/vMhkrxtk4HQqKVcqCMhq6DSXdiFnn4dB4MCSTCShBJ3Tnquup99YrB1KfIkhyznzoMoivBcoYV/vbyadVi7Jm4n2qisArI+dVkyfHh+i4m/oa+LJ3K8vXq7dH17MZMSi1Rr2x4uHjo7DAA3Fmg+5DbUYNKjlEVyiYpLJWKlNuJcuDeQLGs/8kVON4HTFNH4SwiOq/oKGztUte7GaIAGunO50qB5Ez65v4OUPaZI3qj8KVHCs8B5tKVHi1Ki8cE8JRnuYEFSDSrpeqDwO4/SFpUm3ZTZ8XuTjNnAzSC3axYtuF5Qmddi9OgaKuoqHuGaeJOmNVK76YC8pO2FzcArC4bYt2pq8Y6gp3QdAV+XBL8IMGn5Ipt2bKT2kvkHkirhue/6gICa924tH0DfzDYMXYl36YzB66DYYec5JDd7N36fHxO+0ukXkdsMF3mSoGm6GbmQmbS4tze6PSsHRodQRWvO57l7XW7lLtOjjFSToU+Uv7LWJElyyvdVzC/TMuGTmVwawbUxGeGOk/h10EPAQ1CsCjVZyj8RSZao70WC1zXv4TZue6Gq/br0JFS+QVLr3llxrPD+hi4B2QMMQVnXGYj0xgOl6sdrUs9eeqwgfyAwxOZRISFGAsfzuQsPh32ns+bj768pz4clrdpC7KNsNVNjxA9C7QBPXZHcpUfzPnEx9BRoBn3MMMzBDrSniPVLqh9Dxse3ggBKWfH0WMiLXHZKy3fHzINOQaLwYcQo22F0IkMYpieBu+ce5RxwNgDRB1OYp3afM+At22YPFwvE5dlbHfrxNjLrHggv6kc/t9oy5wJWPjrza26OFc7c8sUHHAzMCgULcySyo1asYa1ha6nuism0znxt5KMWyYN5fhSZbyKkTwlq2OUHVr6EysTVhOHUrI7eaTGHRfKdm3natT1opQbtjY3Cudruq0v/dfLsw/wTdutMV7tuCv9JbhFRdseN4HPHl+H7iEexFQvUTehEkkzaFS0mCjZSKru2RMiA4gNzH9Qr6t1WxiNbtlrGBcnCKik8LDSCN20ISlRkCNzAMygLSQsIynQcvpCBM0qHnJ2v5fBg/7J5vZdKHJ8JgigpFBTWg8ZJUeIogKc5mxlWzD8IMe7QZ5caBn9cEbE0e812X7G5y9QROO1MC9ZFKZAOjZ0SpswieUe5rIvVj6XDu5LOppIasZMb5Ft94IfN4TznYwgaUxQFou6AGIB/cI3vZ5c3NZK6EsK/Rd1Mct2eKjz4swovZt2c020WwjbYY1nkAOXVnfgGBqBPL8LkRm121anZeTe3cpkNKdn0uLa9fM2EjaXZxHqpwO5mdgFZRj7/dSPNBhua20Sbgg/xE8AAIs/dPLWO94llvQ+0TANcaTJMEpwNqhRKwiX6Q5pB4/ha8sNbgWASTZdeapl/Gkk3/i27gzitFDNBlda35R7n2XmfxnxnZpQMNYrFPuUvszYaEOti/0WoSizP5gx7Al+ARR8gESm2YhR1Up7honmQ0ia1exQUb8DhgKj9zb+Lpz0ak9NV1O/hma8LTfJQbmbseWnCPr1qYKqNOf+Qbw7kslxtulcjSGiBb6PxE1IP++qRGIMzQTYtAuW/cAMafQEpMKcZW5Fic8DIC1ZlTwKSWBSiPe/IT0A563tTBqHPaQ/IGqDOFPGQ4cG9neGamXQrozLAYChfeKbKHRtVoPPMVMWmAbxqxgSqxunrCwqd9lwOvO9kgyp+V7OTNA0yGS9G6iZJYN5S0xdJOaTwKWycugWigSholZHOYUQV/H88IwF9yfmKl6QHWDUrLg+7h6Hm4U+NmIA/JBuld7iTtoxWGaL3xjOsNei9/KZP2poGuG30253fa46+MPXB+x3KpWhtFstM1SLS/DZzplX+8aF7qEcRdUDyn94U4D6UdUE835kPRbU1NDlZlowzhEON01k6gk5GvabUpRE4viBIdeNa3ZPcAbyU+jY0Ae0rk6ySwDiqWonQmk1SXmQ92i8xPbhx7YVPUCeSj4+h+dHbMZjkz1lgh0zKwe5FPdYaH0wm/bSRdc3fzQb/ylWLPpmTCktBfaMtnoDhv57jhUT+gGzrot+mhiZE6CoVqnWAMt0EPEdprHhTLB0LS+nkQV7HYMTdmFedi4Q15wehRsnpcBk0oAe0+lwszW4289K9LBjTio0Zk55GHRxrMk6aYMxDFPB+e2uteU+KBD7ewTDhEjDcWshe91ULm2/hnBIr3hybAa2LgKxsKNyOB52gAot3UQjrHB24vxJ4mGcWRbghy1D6qbFceQWdsZt1ESFhAm0tolg0hhAJD7313EkHA81p2Wj0cOyAFpHJPesr1LpvdfWd0UKuGRcgDMwoL02UVJyR9o8qKvIgS3EdL9vEQg0owilk7PCuLFyfaifhmmJdzCfp0+FNeB0rhz+Hhco1nRZEbagni9weA/PciN6jOy2+zN7RgFiWYJch2Jr7PbxHpTt9q5EDBKFUJJmP3j3517j9vACjZoFWDDKhxA2lBDAVbmukSb6nySCS28MChz3XLhpXOaHjY6ElcTxPN4CxtQdDcUU+Z9cv8Z/FkHnsgw5Q78Yv3IlEhhV55WIS/yh8c/3mmTfLemRFU6qd5irr5fwF3xwVPTjYeRYBGw/PyP3BQ8tyFCqd7bCNttpSiB8p8YpwQyUpRhQXDeRIQpa+H10M3UnGcY0kpYAX8uq9077rePf87z0zo7OCPaZ+/YJEsp/lnA70ZFXCdhNV7/EKmlwOhZ90nDKF4jjwJ/J/94nm5k9aWstlshu3SuDb/7xU127GMz1RFxt8dYF4T27c70j5aPPDDs27BprqL2PCr+LRDxq7tbkiLqV+UXQduiw1unjkPmesJ42H8wv2CMZBThyZK37HWcWKyWjvtF32SKD56qxq17aO6oYh+QHnpgY4IICAB/AcwPgAIAQAfAXMHCoqIkr8JiqayiwgKmUoHFgq3C8pf+lSoqYeyI036oAAAYAA3AMuv8YxWmuYAXYeA/AAICR7kcV/668mDjmz16hv6GYTxXIPDm8uvrdqEYkxvX4KD1EGO9WJP+2UBJIJbP6/sWEtXXnml15ErO8ZBckvqUgkdAUVNyAH+9CAHIC/GDtj6rrW7TggVY0/OG/wfBuzwl4Wu21YvKKr5dv4dKGr84/ATTQRfwSHkbCYJsginAT/7f3i2xHLZDJBJRjJvfTvkkI9WKXq7a3vSoU1OoQrK5LDhEog+3uCXbqR/qEbOkHw6aI6aqX4qRVVjlpFsMZ7ywDfs0VdKDseCOqH/pTit0fo2mdRR0rG4ooA1gRLuxXohgSbTNHQOe8381zo9mSAmPOIl2afIjtZ+Ws+N3tpxwG7bRj6NOzJRZusFWkpaUGprBdUdqzKo3m8Sj5ODR+1PQV04Dtvjx0dzat3Er7B4wDzmmBbQeCaD4Fo40PZXoRT+40LMhmFfqc26C/94DZuBSMGZjkMWamQoF541DqukAdsKGb04NohCIovivbufrp4jegcSxewVTf6UhqRw/1uN05qzZnIEILHcpzxhGTn07VSintBeYbBzZX3ZqtQGQRU5RyGr54nKIx6l7b0KBTp0iRjXEYPxmZ0cr0fELe8+4hjgw9+cfGjV2PIhrRt3vzWtNxsT2a66HdAlpypz7S1cl2K4WQcmXJW88GBv0M18JSaWN0TY/mUvoCjjv6y+1TtGt3juRW8VyHh8YyzMiOGzATLmsbBA/7U84ohLtuvESo0L4/kk61KJslKMF5zFa9NzGY/NhYgV3uMMfx3bBOAef/YdGS2Aw4VlhRzHjD8w4Q1+WmEr0LRLNklf27KP+kuU0lR2kf0gYBmz6EUwc+p/BhQqGpHtyGRnpKNfzZmm+nzBFTgY828rw0ra4FdnCAVehBUepLC58WBX3jnCo3WBo/eQgYAOfFdzCB/rzmQuM4IWtwrjPznNy6Mv2NfI8wyhSFIbIKm1I0Icz+7Ag0g07keJKck71rhHFs1E9EU3+pXAvixQvTOC/4ebB0xleoZsoRoLTGOJpVWQud4dxEhCUDW3bM/52sJgCM2BsLAAEKJMAOexhInEWUafhUzGXqDbxs4hJkhaSZpPLFv/Ibf9zIY/5WCjCjYqcdLJM47GPjRswmHX4fskoZKYCFWMhyqXoJrKF7dU26x73TiLtfVVxrZDouzo/OVxJ1wFUGTENAdf5D4HfMSZkpyL1sviqJpF0ADX7fbXAcCiYLqKX4VpAOLJL1nPqMQjYajIs60tj1suNKkYNzhQnbWLX9OnxsiOrlcNkxG+xWMXKHJh3ETR+KulGuMcugOk70df8vm2hkERzY8BZ3NngoTPi023W04RUt3j26NVUSV+dMc3ru8g437bz6TZU/7zTY8n9UW5vJ5xLqDH2CnBsy1emF9E+byukGBKKrn3N02Eo2jmQF6QG6HDjlLOnWxz1iH7Xybk9p89qtx14+rtLkOREAloa3SoOVvSzyw+4eopNeENeRCBaBKcMeBJydnIJVdI1w7lYWRG5ZqjMJsTB0mOef6p1zP0CcqTd76blvIPfeD2UsR2joBKlEZI2STCm7e8rjAr8ZJ8gUOmNTbYO7e9ZtGJ6wuDSl/2WySJsDfZw+B0LDuCWwmlN1IXBm8LHcuKSnDB32zL+X5WeS6ufIukp53kD9nteRG0T0I/FHk8RA5My4g3FGEh0ciHDaHQF9URUriVk6MFtWIsti4ahVIWIm4pwNHZ7Hj+MSbrcQa8f5FlGZjB7rBdk21cAdJax87u0/oAwBtBMPblq6jmtMHAt9xZyAxCsC+fxJqmEj1JUbEef+9ywlcI1RrrL5yfN3rSrq0QgR31U+tqmpkaR2fWKJOtO23Piuzefi/8CO+o+bHgl7KR+9lXq3DfihzUEzGXFMRDc41fu34/m/hH90zSzeqSEBABpTmjnvjN5ovae7WCo/m0JVCOdbuuCoauVsob+h6gmENpdTJ5v3Hu7GfsfRInHf5zzATvLkIksY1xXBrOHnM99UyS+d0hDIpbZTOHk/DR5+5LLYLbSEB2Uiv9BDYttBzLsAiFDIiAM2CjS28P7CbguQrRY35OJodrwCsaUx9J4wlB/FRa2eelMX9otrJgZ5o/uTSUC/OwI3iJHSkuViBqef6vkM0gMaI4kLoZUio7EmWMtol5nH+z8KxWI5vww/OdhUNpqbhe3NMAa4n1T1y72JHpSyYjdFIdPJNKydLwKxure62SXZF/KRPus03RHvJZKFQH5nFauCYentqnLryl5ioMkjdwwrYnhuL8q3yFREEv91fdhxTOXEo/Z8USD+DW/O8kJJlGkI043kwvPdmFkvVI8sk0n/MCL4f30/lMZFANz8x/u9ho8w4nSXfu/gfAtbsVSMHl/Y3rH1/+Ec8oP1StmHcQBO8fNUzPX8oiuKu0LF7ZtTzXYP/EqEcBoeAcUHmTUqTOxn8sOGeWdKz+6vK3X3JUM+zIEx9YuweKYWLuwdngpZ2mjQ+E0NOT7YKMFv4cx5bT3llt6Mvk4pWZb9/4zwlYg745y8TmizWzs2gTN5u2okIeps6s/YZnTAKlBVZNQ34s5KG4TdGuDlrd0GuQ2Sqe3OfJ7vT95x/Q5eFHaCfyNSG4Ffcq/cHwMSpqqaGEzKAx3DjXJWDIQSH+W4g8E9lpTcgUtLX08TNcxmiwuia1tWJaayAhVVbx48RheyYSx3o7s9oII4mWBU3U3EA9oRjmjnjfGZDvO03jeHsP28LKvHtK9NgD1JbmxZ+0DaHZ/Jaxu6tzbUDtzdQ/BCp11oJXUD/jV5NsJeE7Dot8+i9uR3KOtu7CQdPzwNu6WdZnKflKN0zanyYLXjRv3XqD43mBr3hDU8Vm7jHE96bCKrAk23t+aHyCgdIQ/Joy+y2w/THfvtrnbNlF20FMF+sf0QV0lGXF0wx6HaL5q+KZJbFa3fGi48K86Gt6fPtpgx8kqc00ls+VyqVIpz2k6YXm18VQan/JGTo8w9L10lTBGXudq/NQCjbK+weN82durVpK9zGGCNgPcnFbPNW3Us14Nr+g/FXIRH6yMBg6pYIHD94UnFelyqIoK++EjQwTrWG0PnO2lsgUVMWoDxWhEXEY5SsCqOYfmE5Nmacl1JvGf5SH4WMuGmFFF4c/c2FQCNCN7shc7L6N8zybTFCaLgkcTMMWwU9v7kdSSIDz0hRYc/qvHmcXKvtK9EhFa+zPOF0MVqY/ifsNgA547SwA7f8yQEfmQw51N5ZAa7CZ1hwpq2Ig=
*/