
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_EXCEPTION_H
#define BOOST_CONTEXT_DETAIL_EXCEPTION_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/fcontext.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

struct forced_unwind {
    fcontext_t  fctx{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool        caught{ false };
#endif

    forced_unwind() = default;

    forced_unwind( fcontext_t fctx_) :
        fctx( fctx_) {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_EXCEPTION_H

/* exception.hpp
hsPRCEgT4pYfGzkt7fbV9N7ToQmsKEe6WZCcnu7Ze04WxmKy2OAqgYjMYDhd/LCzjNGF/PP3pEUUTD8/3yJm/ZtcklpNTbtdzRsiU4KfzqsjTXLcNZkvpageL8+Pb5ELMin54P48u6pYMmSUxXXtvug6c8Vxy6SNNsbZZZ3VqyCldzbtwagV00QnUP/6OEELrf32aufGu1CmuvEvUqLaMVsnYuNZbCWQ5etWUqKMjiyCd6y3sYyrTM2GrFgph1wC+dTM3p4+2GN1Uj9u2p8KAdjfiefVjvVrNL+vcYTePkAUhZfs37XfD0t5vzB+Pjk/3x569nJpfYN7fN8eTb8jr97OaGfQ7yd+CngH+RXKeO9m0F4DZb+ffgwQeb+i23w/eB9DT31/oL8+n6Pqv79ZPx9sH0NXH5dpfcne8Xz9eWd8vykbcnR59nZWJnbuTD+EEHP0YfpnoL9Hosg+Yx+ov5PHDZDAT0/Cbu+YLLa8+uXxuaBKpkH11lmxN1GK53KbHLtcVjfSwxgbSEmqIwFA+j7iaNKGmnjuPJez3tzx8zBiNMNkq5w2c1D49SQrncR2szAhRWUxf7Ii8we4pbgDvO7fnAD68JuJ/mmaYePwwW9i+BMy87UQo7uajzL9nNm9En0Frx+ixDdYADfNc/QyLcPxwjMV6f9LQV/ZDNEMGdPN3LcbbZ4aoYIU/CuTUwo83XmAjg66PHP2tQkLrv8SXwfOxekVCIlSC2O/xUGrrB4ax4qb6/MlCjAj0u8EmGjpwyBSVSrYt2est3FJbXgvJhdR6G9ChMRfIVrblFJu4+v5TZXvfi+EEBTQT6XGfSl4wgXC2bIUSdrxABA/AjD02SPBz5+l5Qz26cRWYs5unmRYEUjmB4HsNz4R6v7QEgR7qhd7uPIqZkIgJDFEh2bOG5SGPy6sAIQQRpNZrBzARkSXsssmW3yuAFE3d0UXNk2uy1WU5dYLyD5wisktX9bTtw33xOr2hfPiTxIK8HnkZ1+eUoAwviQ4Qj9W56/DOMiKdDlePxChR95zXDoeDUjcgtmLNlSH69sLRIgRkvye7jvhAAAs/9NCBPSOQqOQoMRdMI43mI7mr9gx6mVGH3dEK8rVD9zjhbi6XW2PwN/JC44vDGJXjEa/ej+tmEIKFUX6xad2xdXPRSAoGe8ikEbNUB5ePO4QiDN0dUYCVCIP9DxdaefHj3WckTNVJZ0SGjjenEUroIJFFreXm5M6dooWCYYcJqwxsMt19CeIZ6i++e5hgwBbDo2jhM0MUAZZyvKFblOGSGIuciGFEqD+H6JnI4CGvr8G071n4BAwiwcLZ84x/aw1rCD8cxoKcayPVsbRy8G8QFes/WMcWzByPy6fXihI0/jM2a44UR3/4AITWtIpGpFqbGPCLC0EiHic090CD9bBBAwkB/awZ6HcNRi+XbBCjn4L77LV11bdiRi7dG7oHQQWu4/wbrSc7l7zaJ/7SanZ8CPQkbN/tNfkIcTHdykaWXAmtOwzIP1Xt3XDAzCdLYdB+KGRBgcXxOT0YDL5I0vFrJwohGGo8djXhBGTse6L6ejHrfDN5i22lGLKd9hjsIq5OBI/e2jwNkbliHn+Ec2L98NIIhMFsFunbDfauYKMgwzN267siaBYaxTZFOdc3UjVGQM7/ImB9/0/UAbi++1+TLd06yAADIOpwkh3AIFstJxyKFZaKSMsMfS2A/cKXVz1i/DBofE3ygsuwiS0gLyVLmPIM+xogMQ97gjD0SH1HFwxbGyFZlAPMUktyVCveHv/gckH3l44bI6PBck3irbXR3G+w/uBWx5plFEsar3JbDWmyQWjxi86WkmvjxESJbKCVenQWJfI/OqLQfyQMj+6bek/vLtaMPv/XFbp23tDm0hCe9fh+KQ8ohjJAv7gcr7sc7bkTx2Xtbh5zjPF++g78PKH/IlsDu3jcDiBLarztouWN8FVN1pWS8UMpGme0KSxF0a3d/KYFYSgqenBOE8sFyz6qAZyMJCgsvP4ZBZdJ3oOIHR6U6wyCdAWuCHIf0mb/Vgf+mAbMnI9JZoPLu20FAFwtnxeZL5/XB3Ft11Cf1MQBBeFgG5eBhdAaOE1a1caRn0ReTaZDGVqBDgnVcT914h0q3pMXidlHKU5Xl6lra4Xu5wg2cfxZt/BDBxhoD0l/1zOiKux1Uz3ZAgtWHcdS64yL+XbRjaDD1UgsH5MYexmhfJnj1krNKp/UNiy5R+Ui9OJgvEJeyt1xACAc2EX8c4iFRGGhRmUJFH77RGawM4zU4piO6qFSU1JCo35PmsTU5FhAF7wB/FUMHGVcgsbYcw9usFqlYsjLs10PhWI4b/my7EjhzD6iRvccrcfW/uRpXd/EMrevlZBcu7Qt5Zk5ggda5e5Wu/BciD5VNG0Xp+lFhA9RT892ktckqOWBcKA6qFbF8Ovs9IBCcoFj5fouYxpGZ2KC12AmEamKagGZ/LZjHWuw0lia1a2SMt162YBjhOFzEvhYkvB4et6zoW/q+UjhUsMhTxOjvGgBC4JaLCTR6vCIlaNLAby0vRfecQEgEtDWP707HG63qD6XcOn1ufyL7duLxEi9a0XvFQQoQm79UZiVpMTSPqt/IBgTdPUKhMoRhj+zXkICBSGFN29VWxq43eAx6LYD5rNDrxYpVaaqryjYcVleNWS+95nmrhDNrHcthuGZtjYveb82YR1ngXh60WRih2k1yPdDB0GBCdJtIYriXFv9qfvzA24OyHrKJG3c+/714bweOuPHrEXkXS4OnZTxbIPFed8Q3jMLp0XNgr/CK2pOSY7bqYMRqRBqALrnxCDOc6N4pPh5dKsbPfIgTDoNNUSNqRJmYK9B2vKDuN2AiF5ROoqRDhw8SEphY5hJBGsCKSjShydI0N7W1PBVpRWgpnDcPVO0BHhq0ch4ex3+rsB9XXZGZcrZCWmPcPmk7GmWgbUcjcMTN3guN/nZ0oh6NuLp1qpKpXQAL7Iwmynty/OPS3WR9/vW2nS100DmFmVy8A1vXGBq/qJ8Y2oWGlRAtLOEkThgfMSuIDxSibCxo/TLCTr6eLMSu2AZLBpJKELg/3R7oiM/MEZRjYCjj225lHQAIO2PloGMz8BDHd9IIL1wzKUcg1Yl4IpqU7YaO6sehMv4KBmRbOv/JarF4AwnVAclEvKgemn7tV4EPD0WeKqezumeni/KDxgQKqExAUv6zUl7UWA3SCN+RZD4TQd7veBQ+1ybWpTTOCUTlJNQzuhuDQH0pmVrCc6ZyqxJJjzQyAsjva+1zj4yMYCnVaSrW35XdZjed5duDXVX1xgsAKb8Ypa9zntwEp8N5ysbBJqqatZagmu3vxijkYCQ6fgcFg0IKXJ+6aHKogDy63v2ic6y/0QpkpvT+UyYrl6DxZoezKecewvWTc8J7epJkgBlWo95AbCV11IuSX1WrttYy0f/8iGQTjFt4IXdQiAeDMQ/0imhfEDmm+b8NKv61WUZ1/TOITVs1ahz/Q/+VzzTfY94T7prXBO1stK2BD8wUtzgIipohUp6WBGk08+EDhrXoFncAIMs7sI7Ew+zzCb4B4zspNOQr0CUk0bKwi5xDTJo7SYeKTXIBdousckabQkK9ax/1gmYAAxK3P5ux6Pt9py1uVCOKNcIimoGduRYLKkK7l0KJNrPYvXm8liGMvl7Ld12paC2UIQpHMoTG01BLnaSwCSqaCTXRREHmfheXN1SDl3dZ1IM//v+q9DUL2q50J1ZgHi0OSOAxdou7nluScieDIbJt1aohHiUCT4bA4h0y670RcmM2VtLZs+JjMagm0uRoG+XVFkzVOtOzInMrFvVN0DuuTS9mtEiN1ta69Fh0QtyOAF2PVGQApiR9MhEifrCpOz4xI0QRnuUcqfjYXOGsAytY022yCVZ9fefp/+ha1NIvOjtimhdVksyHx+MFWWXkDljkJJBHKRGcu0BL+5Z+GIiCIM9jy3bNIb4qYz3hq6ClviRK+WTaFnTRuvycuBQt52MCHEHlJmgY9HjRg6kXBMLyB+DzPzznyMYvRwREfCORT+ifsPw6bSJnC+i5kjM2upgMAm6nlJik3+17Y3N1FLhomGgdD2oxOAbG0BCA0uCZ/0SgohwUoNVbuiQfNSxCF+ioRZsz7V7itc+4TZv/AS5kOE6aNZMYXLxPQp1ML0kBhvypA3XBAH18F1EppAVNGFN3J+pP6wvtw8gQh4ya/z6FFqEOe7EsDZU2XcOPG7MfAqECMwhmGCYQWnZii3lUlkseVhybCzOs3uXIUO0oAVSUkp8VBJPcUR/CjyLBwo9P/ExCelkMbsMgLCplnFrD26NlfU4hLgIO+foVPbsBckeqBhlOIu2vR0HxAs5Xah5zxxWJZgGe5d5NpwGWx+zth4wMqbqsivKi/gk99oc6eK9wncDmu9yd47bN3Mnkn8/tkbR9c/AKqJd2cB3asfs6Uwh9WMlCsx1cjkF8UbK1tKUZycnPmv5L4IiHVe3AEBteQig/Iyajm5dsExUuGYZhL5QNWxBwhwOTom07DjFXFO14FsyRXTCRtRRjjYYPrMj6REysmxvEcHul6D0/azAlffqw8gXvnaqx9WFZDkDPNz6HN752Afj7+8FHUAObaaKBz7WbhuHaG7liiqcHOeBqi9PYy5hTYEew25emzhn7/n0I3aSMJ+hLHnyli2gERK9fBpXZNZCwmNLdsEDYRmsCIHxenqJOWkcolkWDrhsXJlv+zHt5wOiRdOCqjsYonZsmoKbff7wwc61zhLksoBN47ZBItdRNg+xBUdtk+N4DFLF3Q5nM4D3uqpbHANc1Ru1eL/5QXSUiYmnF41IHcXoFxeyL2dkU9CLF3QVn1fGAsnyOFBDGlZ1xo1SXnWF+kyg1gOEb0PEm0q6QaSYcwmWX/7KAMFARKSavUaiRE/5GqwCefLVM7gyjeOTzthJC9bhfQPYrTQvEIvOSFj3nN4phOsmcjb8GjRTz2L42Nr95/sTfhhdMw62SsHFrKlESb4pzOfCTEGNpJ+7hdNHueZvVHXS/dGgDTHjgNNaytFDw+2eMXQSpFuMryyZpGDQd4SvtZuN0qRtucinnCZqYRa9UYIRHA0mezrZJTVmSgt1KmukC2bcOqeRcbVvPQ0i7683+tPo/MDKhq69gajgE0ycIT0it07U2/rqfQHzIRhAs+oxtKtuTcNiW67a4QBfIW25Zo7dU6kr30yobhhCChZ55DoknK33aRiHSpQLaSH/5/y7RkMJSQl9jQ+6i08RmGuJkc5n4QNGICSMAUKIcbkHYLBicBRqBPJbpr3djpPwYhl/iypGSCuHu7WEFTvroN45ZGAW1G05+6WUgn4dAOx90hDUoVezQNxuSAv/jGJ/2AKvBtj0fwSwm6VLeGNNtISwrcaCy0Hsw4pOg0znr2MUfs9UhOch590slM5WVPLTz8g2mKs7x7TqVbnTtldWSI41hf/hynGN5CXQy/3mwehYNgJnEbIxiP/cWqWR6fDxuxAcA06Su5SepOpJBMskHvyAba6UrAu+o8ybCQsC+xQpfA9LsDDMSKiWlPr/CFdPghjOdCH5toSMCT96i28mQXy+9EEF1/PdPILQYkMBbVjU/wkflgw9ZA58BOwRfZoxpmpZFkEn4OlCpaQhrVXcP3QnxlFIa5oOPyNhRl62aEqUXQLR8hKm1RvYcdSWI516ghhJJapBlA3yEm5JcGOZDGVRA/0hNQ/OSRstgNp+xoQbfjXRWWARqtFiut+YBgP9Z7D7BxbALU4A/sybJVgJgD6CJrFnqENAQV86bbrF6GALAYS0h+rR/0Y8G7avrusrl3rxGFXK52HdgGcecwBV5MEIKkMSWygNX+tBlBmQmtJp/E7JZzi8E3kU8V59Gl3OhKABUvpC6AzIh9qBtR1ZAZUJCfnrLFhmhmt8ewnjUnH+Unv86fa5g6XkvxrS6OEC4DlfKU6SEBBJAVzRvBSllhoH0ZbBxB6+/01egBMcGuy41hfVeJGteYGLR4lJQJvnOKKkF8LNzxhvLesliU0IWdQNwOrzEh/JiKD5/vyH3vkssW2O4kRa3OWsaeZQDVAXaZ2OSmIE3kA+t+nku6JewsCaMp0gk9wAuyxwUfD090GuLzesOXMhqgj4CIMFOoSU+kFskP+qrHF6mSaLS7NAA6f3zePXNUNwFWfSB3zbg9yWlgXGV5Bj7N0tAALNQdIOgNbIIPJb8B+hKSOOFkWyr0sD8DCRwyg8G2czr4h3GiX25S10lPSBJzJGaSHGY9kg5CAhlB15FMsQLsNPEA1hwM0HYczCfdIh4xlLV4DRdcJSYVL+j9aNDQWBN5wJTtPl3bqvIEe19vl2AnUJtuWRJd/i/UXH0gRlMpRQhhmQ8BNcZU4100Cnhmg8SsVfcZIHrnlWeCZtwf2fLYEYgrT2/WToAq5RIP2gjGGVe0GdF87BdEivi4nDLV6SgLSV69xicXyo+Ytsc/u8YHvefmVm6XAVDTEkTenoeC/iwkQO0WFIpVACjUe10xqGKkw0/+rJyHG844Cv+oX+us//d6ytPdp8rD7CpVoarFOUWu+NqI69ma5LvTht2JOlv6W3mJuOHgAC0+ROGMRN8tAmwCQgA+AjHfjzodbxBYhBYEZKyygpYLF6CqyzcZIIR7YFfPQIHYt/xHoWgly5cHCfcxqWfGZ/TNvXyRk5KeS4RK/3o5nJT9357JRTwG9jJm2Be4JSR+bXV7oMPe2qDiTtpIzdyt0VQr+Ng4TE8bDSZRB8LyGcWcH6A3gclZAf32FyOsM34JR8VYqIfcxSMMc1ypbGvrig03OWYrv7SAnmV+jeRYPK9rHoQfzbjazAw2PqaIdUzroCzrlvKR7BlqaEisD+ZC1nvmou8QHZL978SWwjvncex9AIJt5jz1oDBJ6Z/iQdDEFOwMoEe4eQHwKyoV2lVJnSLNh3MBKzlUMqYIhKb22lR7X8Hfkrk4O2KmlnpotQDIDrkkdz5jpTxehyB2UTnE8NloWX1H4eCUSvgCfOIieT4AfDvoFEKwHZeQiJahZibMsd4IkaT44fu4igxE2PlFdbp4KbgmxKNsBna7QyqglNeNgdWC+3NTknbrr7lj4mXbqgDxb4fXWpQUFgsciP/nGMczZ+iEpHHwMfa7gQhS5gDaTDb39w0QkaCAE//gkMw8wY1tGOrHbaVOufM+tdL/0QgST05NtZznd3KQky71YDThtNH5uaHyjMWVPHvr2dD4xQAAQOkYdRYzT9vcoAP00Sju8l9VQquh33B9MptjPMebXUR3G9I+/Xcdzh8rD0V7xq8DwMkBxjF0r66j97JO92bQWC5BZP6O8L9qc4HH5pn1+IVo63iwAwyiZWfk4fygDUW5Ou5S6ag9DVPu8WvoSh+0FPobmGFQS3kj5nWR8ajH1xkyymccDdokcsEVcsvn07te8s7Qix/GpxoLOrKQx6kATdxwC7kxCl3rZ80PUUMohVL9xOqwm414TBpQd9Kjbfh7AWdVowwxw8KNouKgjlR+sQzHO7r7Gu74S25r2ruy4ig79UmKWTY7tAMf+efS6+NpVA1AxxhOuex6Euv7821eC4PSan35f3dmRwIS/EbVkMZkUzcwatizhrMg4bXZaRjoIw5yYqCoZjWJNskJpTGE/BfN3dR54s2/AZSb51kzEYo1xi8NXfABZKB3jWvAS318EOk3ZjihkrnJlfEpNn8bIf7JtIKbNShY+clz2JWCJ1zJrn+ctQCdp5I6r7SyJu3D/bDODBYLJMAqydfxINxw3GgTUSlCBjgu1cvGC0gU6df0XH+74jPGRSA0J77/jomjEA9YeGWp/xgIVJHWrswxqu4i0ZosAsGsm4MA9LQ1CRuitE/qHY9LBrRg/yCA2sUOFsogt27alIK+fEQ9qtGJ+x29OXR14ILYgSV7tXE8COcOl9IrPYhPuDDyn4a6wpI1fwRD4SL2U8Yi/lFIYfu9qk1EDk+obQ7oFdu/JgNQ5Mfqdp1lYvg53guNyCtyFjoOMo70f/A7z9Mqw4StEQA2rxsqMNhAW2GqHbJfEL01vM9qWTlAA0QS9WZljWiSlTYGvZfypA317RL4y5hQhZId07lIK3+D+71ckQx1FApTcxqM9Rm6W09dP279MR4g8VpZOaPwu+xpx39wo5P6Na1dokDO9NZVHZgCFTJxiYZUmDExWFHSk8WJDteUXsun9mGc8pSecnJ7UA48d6VHfiQs23aIdiLqobTuoEy9EDIsDMMa3Ik4AQCeA/XUwpwJRz7y/sOSSH8sGEnWN9VWAFFmABRQcRh5+Hm7gil3YAwDMtVsQISXBXNNgPn5UgPS31/FPtlbWi9U+3wY3IsPlUYnh8ood4SyB5PVSSO9x2n+Jqra9Mx1qX+7KBgTVzRdZSGJUwLA+yY2beeeyfamzAPJnPHlDGSdQPAC0nQD1pvcgph9fvLW33HDTFA4HLie4rBqOk1vrF/TxEknipdN56/MZYjXiuFcGQs9hYd3DHUDjw/8oZWnoSpeXl1U9sNB2OBGoppjkhFcPcGVAoAeaJPW6l5EY7xss7jHQLWa1pp215ByrJ7GFCLy6vNWHPJ9UHym96vk6AGvhn9jJTulNbB30ax9Mm2UIlbKV60J1dBMuwaUn4OWwgJRFMhQetR8PqCGszTPkWPYxC7eUBk2N8sWBvl4S2m2NKK7H4C1pw0mhukRnnETsWNbBkvfhZQ25KhvK3DB/gOD3UnqqML8R86DEA2AQh50v7JuM87FiME2QHDRoK/+1jSp+7QL59yDnodcMg+DSYXMHCNOCjt+PGwA76ePFlzOMu90sOjWwKLQzHtTQdXhek0jOte+zz8JfqL9N7hhJGCO6PWpmJI8lj85pkc5oXRSelGq1kN2aEnCYkwVM6tyXc2uxR5chfhSE1g7d8kXBY1kSq1z7ShSASr7Zbhy2oVoerd3BuabFqH2TyCL9r9D47h1iTd5whtGYjpFFuRl9cT3kn6CGEG3QB4SZQro0YjO7FrhTSNU6s/8s1xp/QT9awROPAMlOkGjJcaOjYAlG3p+HgSRwf3E062jw5JZk48kdYT6SElxeYISxn4dUuBNMo9de5ztuOtba7JiVegPuKF65Rmpt9V2LIltTyA0pvlN+wNGuuBpmYgDuXtT1ZMLJtvQ8TeRpBhU6MKmDcZ1uH8O6tOuukpCXAyKII6I=
*/