//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_HPP
#define BOOST_COMPUTE_UTILITY_HPP

#include <boost/compute/utility/dim.hpp>
#include <boost/compute/utility/extents.hpp>
#include <boost/compute/utility/invoke.hpp>
#include <boost/compute/utility/program_cache.hpp>
#include <boost/compute/utility/source.hpp>
#include <boost/compute/utility/wait_list.hpp>

#endif // BOOST_COMPUTE_UTILITY_HPP

/* utility.hpp
qTNwZ4iC0ngiClWMM9JqScQynZHXCd1r4GVohTh+P8bwf4N+/hjjAZe1RmfVoGWUvPRkIDP2qNY0RMrmUm0L/RhoseRhGNToX3WeEfcEXAilcKDFBatCnR5dhUpl5ucYmjy3ppU0zOc2+PE5nl7EScXG1QgLYOOhPjnhifAmlqVtwd8W7Zb5hYyKPXWHEIbvpRxxym0ir3DMd9gQi5KU6r9xfiEdH82WtpVEoumoo04Ef8nKqYzXga6SYkl6QmfVNb0fNEawy3wwsbYCWIHYeewA6ISJrNIOupFdK3JycU147cpoMAj+aoZd+cggcEhr7GQiMEgWysADcWRP/qz0V84LsB+A6bqnPi728vFal5V2O22LY1mtRRhmSw3lkekwyO/DTSq07ifS9l+tbDrQjo1xF+xXX5FJanrBRmsUvBSLX/YAxeKvsP5hamIUB4AAgENLAQCA/38NUHxJsTK+WBmj8XRlWOscGjA2OZQTczX+En8Ob8Sdn1h6KHu+n10Hfg7yFTuCI4lzUnQaOYXkv2fwc6B/fqETZYqagwF69+PI8M4n9pKxbkvMLAU4rdeFFps/IE+hQi/t96NZKg0r3dsHQqnXHbaDb9RIUnEUW2lIRZRZd7E6pIwedkC9cCydeePwYzcQiNn1EnTLXkYrhugUXW3JxcMIp7TBictvkU+Arfe62BFUxlnSTsOzfMw7NMxr6BcjOjesJnxqIseQBptlv9g7FLL6MHKfh04ASO+4GgFlpc+yA6jO2lcRwFl47FavQweMT+3BrUdi3Cl4utene+0iB2PXxh6GOiIRQQMZTTE0fZYNpjIu9TykPIznW6ptQQV5mtVjWEm/NTuYs4LOajbhM//J34XYg66x26OMDCQGhSGRo521/0AZc+FnIBlOUdQ2G3PRPjQL6dQxAp1oRX0BCiYn+0LH0OjCJzsIpHSmPWKzKNNwlz0JeZ0Z5RslHrYlQ9ejtHiaOozNshlxQ2+f1ij9EKdJZ2lg3ZXqlrN0wMxIX+rUQhk0PKKUzcrGqjLoxnf8jc49S/8ZI651iLutVuVcsbMLYeo6rVMR8twm2m/CpzQlsQmFu6JGK7tyLjtH67LRqUnF9LAa6YRliviiIPsGPAFJhLKYBmZvdtL4Q8WCJ8I5iWNEuByjrODELH0jlm61Kel6hV3r+lICiKvAKRWP54iSAV6pD8epfgyPMf+WhPWDgUbxKC6bU6CVo95en6+MgiS7URGVBfRwrx7u45bmuMD0lV5ftA5XuS+URrXKkKP/ugeXXyBa0kuLNggrKt/bh6eSvafyvb3ssC8QCPAvGFg548oCZ3YQxGECfBN0odPE0DpcXPDOIj49aproMnJd7FdmFSt3FquB6CvYAxqymDzxn7cOoQU3zC9PiMWmg/jF0A08t2+hwOU/5NN4IHvsfOIx1QGiPTF8yMLz9uDhxMJFZ0SD8neRf2hN0lWRexkOi/Ya7TrI7bcMboWaqXHaO6Z/jdE5q5Ll55f742KBEVI+M2Qu1IuIGbZJMDMKxJyYPMA8Qy6Y9NCwxYjg14EhobpCp/JzgXj4/2bi0kTc19TF5xu62NTBw1EHGxr4MJ+/MyWQmoyjnyO3JyjtlLQarbQJFFHnD/0QM6rM93pNnHygQhy51Tr7zWwXu9mG24al/IZymGoytv0RSDATC5PKk1gIjW/8IyYfrN+ZZdFLekUN+lbaax1kk6wajmnsPzkG9DiBshyTufvuhqf+Vm8HjqZXdOoVXK/oBgM2lAH28Fk7fZ6vnbVo14D5WUnZAMqNAX71TrIIrgNpgSe5+XV/JYV6aVlZcEm6rCuD3DlotuKmY8AfLeng+zKtFgbjJDfxwBvZ7PlSWVjQ7PnS+Wyzp8VZexcliYRsd0aLrAOfOhv2Dnw4oq2UD5QB3sK9C9jhvZ+k6aswlKSPt6Lj0AmOAza8WOb9dZaKXbSfGezrF9p+l9xV7+AbManj1p1ZqZtihtIDG6tovk0ZE+C3rgZ2EDk2lMioRFLMoNE7yFbPY4V50RJ7qU8Po7gDysIMXyAjxFmLAg9vLXA3IfrVe1hmzdz5WIjsju527HZWNF9GmWubV3z/e48CzDqUkI1pp22TPFJNQWnXqCMwzhzCuKk4TpuEo5KBZ4Dt+MCJcSe0v/ZpLXno+zh6jDsmkgudghrfLALLZ6qP//AzIZIrB72akxgre6KJlmYacO63pKi/n+4oMYQ3f24p+DzFCq8F38cfLbbzUU8OCmMvjdcaLx8wX46hlxjmmwoc2v8q3W5CnaM5rns5ynw0rZE7ez0tSiXP+CqOqSZ9/MPWfiC4HVgSHcIMsFFiU8CcmFwjMsF0VUdppCRBaOzJ6EPlAW1K6ag8nrZlFX2spLeMP4jx1pJe/mIbcaxDb8TB9UacpUz74K/s6Rdgt4AQ8XK9iV6Twcwnbqf0i9D0xr/g+poO0BecCA3f0/CTbNd8PfyGXtGmVxzSK/brFc16BR3lqxjSwx24mHBJddHa6oVlJ61XTMgBXp/KDsDfK9FCymLXmhYOGEnRkjdw0xd59Uo/boSo79NYTG2OXc+vr0Dj1c6u5dv/iDdLFL+Q4+JPB/ECD8Db+azNvR73KpURvLEVY7HKO6yNucS8u6GfVqZ2xi6SrZdR62xY+nyh2TpL+p9Y9c8w/GqaBl/w5Tcy6ankDZgtvwUe+QhAQksQDx81po8DpKz5I5AU2MjrKjhYIDwDlPnJMVSEB4Hq7oqnnNXp45fFkbYUcOFf/QnIO9fOimy74xiACQ953lYz+4vutaqjawb/AUWqq78Oj42CxPMZhn6rckPQQrGVPoqt8Mf6KWw3hlGnSM5P3+wH3RN7JDQcNCxFdXxRip74eDtUjha53Ivsam4gEPL5QkLswFeBULrIGYJFHDvPLIK3fMeaLIuPX/UGipFsRtMKjk3DLT34p08X4H7YUYolxr6fxi7kg68A5zgsIVvj7Yik09uQ73W1j1/5PCBEtGbeAeiP0u0uoeHR+hfJgB7SPfojNv0Ru/6Igx9olKdceH8/oqweszp5636AZG6lKMMsp9YiVJ8WaSrq1VXS9tSb9icY2GTmdvrbQX9JbFKgWW/qor9o2EhdbwRUYAJoya6mt7X0dw395fQXkyF00oY6mZR6E9nKpC91cm71JpR0rXUozu5FuPfh3RMH+JFtJHtRUGwdAoRVV1mU8WjSsuoqaXkDfYcHErbpYj5tiRm6Px/j3Tla5VKL6gQBmGZYttPQ8Du8qOfnLcYuLCtx+IMCB33sT5ipRrsxfpRxd58iCTA2NNzPF/82y7JggYw934+pYI6Q4B9ePCAFHZCt8wog25yXsyxBPN/CHylBdduml/Rhtt6Qpw30+ERUJ0Mv43LItsFyeB4p/erLROkd3TBjSWXcxaAMuT+Da8hX3gdwxt27cHtbHckex61tbvlEiFhMpuVgepCPe3G8ViAylPSg9uWfn6KVw6Ff3rwPVs6OLkRqZoEIBHH3DhbV1xi0PUw5z7RHMgXYHsp8QdxfCrr2ZLuCha9iGBI7CU56FXXa++3I27mxi7+7koMqbaNK2YEAexNLA/zB07CObu+jE0gPvw7ASHvOZzNAbkwPDHO1MMICI9bVelz8ZqgpeZ0y7Rw7ZUolqJj8veC2HvsPQGXI3liKG0KH/kCaAqQ/8TPv+zIuj6/t3wuwAEoDPP4F0fPCAJUvOdBvUFcm3dThqD7+EVQK2flTf0WtDmLqMP/jX9ED7WNUgZImfwbojM53LQBRjftDmSGLcxfWBsYKrrw7F/eTcCWW4Y4gnRoEeTOxoB9PGS57rd+41or/GH8e4LE/0F7UP3cq0SUtquK3fIyur9ubrY4F9W71+YL3ysAK//k+tM6KYs8mDL8N3yQNv/xbzzJ/S6UNA+LDHR6vXMqt/4ah2fEyA2ISpT4OeVpxL4TuLKIt1diPcXtYypS1hzHhMReqZOjh8QBlIdgf45k3mxXbmAsmPYnNdwh1iBXasdsf5H9YRicnCD9mAmSeCNy1ENDicnuHlGcF5rh2o/OwDmQJ7pzm4eHoo7hALnkJjdRuzB6lUwuqI4iXIPFMzzCgGxc5W1/AfXAuThLBe/l7eyTBwX7sJYH46TuYSwo1X3phLK0ueGjCqHgQk7z81B10y//j+mEWFu72gWL1J3Kj2BE+t5o0xqVgFQDdYv5EX6ykE+zuDH7wjjiN2PjjBcjFaq9WPWStHiWWnSJ4kM5qL3/6ARJNzEXZD2+gJBf4fu3EAYEHHBfuQlXAT/yebIggBskbrx8PGLjz97g3DUrdodOxQz2CBwD5KJowHUvkHzdB2xPBqj1ongMub3sRVmSlNWC83tbcLwI+1D7FGGoURvF5MLK4lj/5OxQx1Fi+MM4AfDV5QGBo9M5MMC3AqJ8H/wfzluYgTqbdjXulztofZFK8fvkeMiCmuiMIoDJZnlHEADjI0asoBMaoa2T8h3Yi4/eMzUQhtA3qkeEjLaBesoz2m4bSNr1iu17RqFe8wS+4ydBv5/TRvPHcFf8bqE9K4LXKQjogcPRNzM1uNrK4+S2huJkjH90gC238bdyzW4XmTzSKGeqlujw4UOTwBcfbyLiSNrc8A4BnBlyo6o5DDTxw7WN02C84zLhk6Hhw0gDa9Yj4QoMqegQT7XkB8KPMufeJHTMwSf1MKqydAFSgF9zx27igjswOhpDQD10q6fAYnj2MYpHnbWdtFTwFp00Fo2zrIkmLEL1HsLQDuSwTbGVcMEYW+05UjDuGjINaINbuhQLwvnJthlsgTy/qETwoIKLy2FqzTx4cCE4wa2EZdoAX1oAtIx1nu/sZrLW8LTR1cSAaWQKDlPk4i9A9XHikBEv40j+bJ1kNxKyf/LVopVMG09CJpfHzafwQaS5Jq0y+arHVYqbAE7/wIzMHAWWb8EBSzl10+JrIzRf+BCVhz8/TTERF6YgrmHPH5H94zNOYE//9JV+LfnphdUZGYZM38XWgNbIU/rsH9eyBXmLrywImv13XjMeblVw0FY0zgPIkCt8CVWMjDA5cubsflcgyL4heqD5Cn29rtYzfDvINNz78cm78fZgXI1SgL/pDNDwKbdGSlaXyrIKPP/Aj2h1idv7T/DiReAYAAiz901qy3gafPNkxno5/HWMl7QMdvoEPS2UpXocBrvEaPx4G2IGntpzRW9LkbXCRXjrE1cFOM1ujxKA8cSxylj6HdmkHDfy3B2HeRlMnYobaQRNPi3EnAMYpduzHWdz202Tdv+Icolg3ZNNtr4kcH/rBCJZBoAvxvkaacshaViZ7kLMVS21cz092hfk+/2rY91NAXJIYFgY1CwOpHeiRNXiHSab+DP7PiGZ6pIF+dxMSquBva0SBv2gBFsVy0eOSrIAFxis7bsMiN/uQ/rRUdmwn9OUCewpiXkZ/PcTOzl8ouO9KS1BeJ0I0IzGOz3wiKN8yUzptI+K8JNRNZfydpxBTKEULhA7ALMsHEbwGM6g9b+IEwz+Xk8MDZ3bP24mk8Tme0w+9n1g8GfyW732dKvcuxQ3IpGz8Pe6LEc+iYP5wGwhmYnR8entbvwETeHd8Aiw5MDJ6rkGjtGtuPLXTo6EzOvWf0WntGZ0uO6PTthmDIqkX7txGCvAfL0pXqLgxhNrvrhfpxks2yCd8Rhr+JX5yl9TwqIdUzC8pBC92ceSEgnuKL/E00FtsTmWkufpyXzBvP148ui2U5+OHoSeUW/x3L6JkyiYhhg2skwZE05KHs11+/ji8WgArFEpjYN2zVWjyiKWnYhWJn/AO+oKXOKDRbH6y2XZ4Q2A8cul3gzHHBOPis8D4OQ6ovuQH3cOnrh0ko6Do5X48g0i3HjSu32MmElOunIJTBwtGmWEmAo2W2dLSNw+CZL5IGnGYYkZpLsPQgwF9FUuj3aj1p43bZBsbwGw1PK0tvz0ttC3oulm0Lei7WVozbwPwzzwrAnIMnOEA3llzeeNpgTsphqOHLRcnmqB71GrFh55Jm0+LZAe4SfsXLFnFE83YKuxisV6H/6Vm2oPNtNQWAvsFL3jFG7vs+lKbbocqrkTYSq/BVol4LKtbI72jObQBaxxuuJ7V022CVtGwXxrm1yZLOmjXAJ+0TWj3WuSrkIX/Y81XgJM1EifokFgWtZhO37znwOlD75bX3fBtp28rXYrwvBlDBMAkavg5L55O2OirbjjbRtdeIwLoJUOKWuZn1+C8A6HrxAehq1lcfOBpDdtCVwMVseRaLAldxTqgvAXKr4Lya8UH4KOyn9lYB7vRkX8gHy+8ZeX2d+ORo0o6m2cLpVM2MQsPlYldOFY6OL1XzRM5wc3GLm2euds3FY+KTJjSnOtyRtDfd1fY1QzeeQuscqtf+OajjfePV+kOSszeCt77Qg7mI4/20+mF0SkBUQuece7zBxuH5bi402/Ekh4M4EWgP8lMs7B4GW39yfs9t1+DKapNeIUnLLVrMVezHXM1rw4bF3y2+0IWv3gYnMh2eb8nXT8r7/dk3k6tK10dDTWCY4zEKJn+gnNL7mRS5J64HOZkhzlxF0gn8PdQ3aKLG/DxfABE7MRKLM4vQKj6UnInhmTuRPV9ZcYJM5lYUUw5FEM62AD4iCkV/d64nXUojpAdpglleVuoLA1K0mTJeFlihRJrskRg3tGQx3uq6pmFzNu32EzgTrD40lQW/9FzS47nuiTrBiiWm7sdDfyIMGlzhKt3GLRZnqDNvZi9HA9I2jx8B9JmMd5bA4Kijbfb0ozFoNfgactFLT2r9mQk9lvALy2aDgO1FceFOwM5Rfk+sJ/PuStjSkcudN53VwbCeZ5Qc9nc6an5mQ14uB7NImD+bIu2YjrSYSX0w26ejmsSz4embNzg/ls1DlWBQ82UQxnDwIhArMg/H2o7DnUdlHqOAHzWaHn2PNGA+V0sjrs74+ANDol3NHjiioMeA6LBRSd/FhOAZ8/4gzmJGV9zxoxPLyQw8tAFRjByk2DgTcGYI3Wx12VMPNfSeMefTNle6i9oBvfcO+Suo8v+Hi0LYCrIHyjKLs92PpeQTWx8DZuFGwyY2eZLEXO35gUtvwYxw+YBu8YHPh4n5pg7VHZ4iTuRd0cE3uaLheowPKqMabY24LRCFF40eFVk8cJoHd3KyH+rnxbmZUXPwG9wYOiAAYjH/yyzglykxF+NNjsFsCh/vQgPIWKyK74paC44GumvvjgQOVqZ5/kl3e2ay16jScx4Snt0mkWxFt7k+aDq48WLWni1bCuTp3HbhZ2MnHCuxhRH877rDGvyvmvMe5Orgc1Yj2fj5kxT7Xih9aeW5C4xpe85Co7qc6Z59ikj5LasXmKP2bQSu/DsU+90P0kXT49gt+fN41PBwiw46qG7ptU5jPARu8Szr+r7kgzhSwwSOGpA7Ga4y+3hEe7SaUq67rUXrzhuICI2kv8RRIC7fEjFnWF3uUtJuTu84Cg0qxrlLneow8zrr+EpWx0GDZyR69HAVO2yPrLh2VcT96CpibwJMs2VsoFTebGnhs6RjvPUEKyjmC5v0a0BXoll8Qu8uN96xlk2aHWT0ep6o9UVRqtpNSDEg1Vqrosv8KFkwI0RmY23Nd2CBz6KsNODs7HTRWfuJVVONjrNMzq9KgEK3pOgOnFNUDRZHkND48ARXerCK3Eo0zPWw5fONrnhf57d5JidF0J9rU2cBci/amWHVsO/s9VMo9U1RqvJspUfkMKKHBR9FTnNGNT3OrT7HRa9CBlvEaDj9VkSx/b/LRAOaBSZ9S3C4CFD5+oorX/J+jUJWRBWDEHPZtSwOangyEN4hFwL5lvMcQCfP+CwaLfbBXuSbiAdua4p17XY8251GnuLPUnXbNbLF+vhhVGeqdfTlcOJ4xWFAOXHNxmU/l/PbQa0+u1NZ88NGl1nNLrSaHQR+6Vs9AtW7tB9M1i5S/cVolxemRj+bqMjx/929NnQKP+7Rr/MaHSh0Sg72ajEoRfPluP13ZigZA0uQEyETC9oboEOcoyGI1MXWEtP043G9kKZmTRCsvx6kGURUXmjp4kauQ2ZZWvEpaCMBVtGa3aJAiDhKRlaGTvHQy2rDgJnmvu0rbH/5hU3JpbEL6V49UeOVl8EEF1iQHQBe0Uu3jq2bLJHtSv2QhBeH0E/MuNt3I3/+0U1DZAQKzwbf4iGTImRpNkNwrYRVerhRT3n/M7cY/E6yvwFJ0Cr5QbcJLKrr4ycgKVFv8PXJEX37Xl4iJpPDYJ377UrY2bJKlXvkpAjCoCnMZ21xMBfLEyigC5M9do97dVFeDzN80H1TJjSDzz7wtcHpJKJ2lax6ZH+yss9X4QvKWNP04gfsPFr9dyFHkpoCTtZDZk4MxpkSj6P33CGFgqwQU+Fw1n7Cq5/VEf4uQT2FLb1/NkZ/RM+rZIqYT3oFfY4YiZy0Ln691jjLWf0BeSdsEMw22pQRlFKtVPBUrHP420lVgvYfLKMDy/LsMTG4SWmFvgFjr1ql28wTl0yDyyvxxuI6JGD1eNgoiWeveGb2VM0dsWQZ/wvlHMKPXur/jN5xx6lyNotHrpqT/mbcbke6ZRdpFPkyQi0kN7iFpx3aErjenTAT6wDBxz3uh3sZHD+g2BnHdHVdj18SPe28Sm3UOwx8glCc8Jd4XLWfgA/3YsUZ+07ZKXglVmet5VsvuZm/IoEKZHsW1CJxCYFgxjJv/1q8H7kXjh4A8PA3FwLNhyaRrTb0xF91ZeOV/jQlW5Mm4aXkoYPNSER6AJ8zAU8pqudrd4OJyJv/c1k3I6XU3oDxh9xAG+ro8dmMgQ6WAFdJMGOhMBC6+TN98UxpCM3GNrBDlLbxJOT6FsLePpIdVJshbXy0nUyOGERDb2U1RbAA84vIkjeY9Hd6EFG1S7jOrdMXQLbEmtNOql5qad3/1dCaKoUQj+e+X9UJ1NAp10787t02v8w4BQ54Fcz/o8DToJGf5qRkBI1qDcizY/SJ2Wivqzn7tiT6/JHl2Z4PlhUbWP7Yulac4Y85txinE23M8wOa/ClnYkjw4SMjQcAPMbABYaeyP6F9nMwI84v9Byo6sIgR/UFuG+X6Cd2Ls7Jym7KA1Ps0hmYSuXQ7GdqL5pSDBfS1ISWP6N3Z/GKT1Hg2c25ldhll1/wYx7Dyj3J87bJ01mLxKb9KALFGbL/POO7DMgjKDlHmaL9byjbWhDn8VRj7FoD099PGGM=
*/