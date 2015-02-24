#include "font.h"


namespace MOSS { namespace Graphics { namespace Font {


//256 characters, each 8x8 pixel-bits, packed into a single 8-byte long long (uint64_t) each
uint64_t font[256 * 8*8 / 8] = {0x0ULL,0x7e81a5819db9817eULL,0x7effdbffe3c7ff7eULL,0x6cfefefe7c381000ULL,0x10387cfe7c381000ULL,0x387c38fefe10107cULL,0x183c7eff7e187eULL,0x183c3c180000ULL,0xffffe7c3c3e7ffffULL,0x3c664242663c00ULL,0xffc399bdbd99c3ffULL,0xf070f7dcccccc78ULL,0x3c6666663c187e18ULL,0x3f333f303070f0e0ULL,0x7f637f636367e6c0ULL,0x995a3ce7e73c5a99ULL,0x80e0f8fef8e08000ULL,0x20e3efe3e0e0200ULL,0x183c7e18187e3c18ULL,0x6666666666006600ULL,0x7fdbdb7b1b1b1b00ULL,0x3f607c66663e06fcULL,0x7e7e7e00ULL,0x183c7e187e3c18ffULL,0x183c7e1818181800ULL,0x181818187e3c1800ULL,0x180cfe0c180000ULL,0x3060fe60300000ULL,0xc0c0c0fe0000ULL,0x2466ff66240000ULL,0x183c7effff0000ULL,0xffff7e3c180000ULL,0x0ULL,0x1818181818001800ULL,0x6c6c6c0000000000ULL,0x6c6cfe6cfe6c6c00ULL,0x187ec07c06fc1800ULL,0xc6cc183066c600ULL,0x386c3876dccc7600ULL,0x3030600000000000ULL,0xc18303030180c00ULL,0x30180c0c0c183000ULL,0x663cff3c660000ULL,0x18187e18180000ULL,0x181830ULL,0x7e00000000ULL,0x181800ULL,0x60c183060c08000ULL,0x7ccedef6e6c67c00ULL,0x1838181818187e00ULL,0x7cc6067cc0c0fe00ULL,0xfc06063c0606fc00ULL,0xcccccccfe0c0c00ULL,0xfec0fc0606c67c00ULL,0x7cc0c0fcc6c67c00ULL,0xfe06060c18303000ULL,0x7cc6c67cc6c67c00ULL,0x7cc6c67e06067c00ULL,0x18180000181800ULL,0x18180000181830ULL,0xc18306030180c00ULL,0x7e007e000000ULL,0x30180c060c183000ULL,0x3c660c1818001800ULL,0x7cc6dededec07e00ULL,0x386cc6c6fec6c600ULL,0xfcc6c6fcc6c6fc00ULL,0x7cc6c0c0c0c67c00ULL,0xf8ccc6c6c6ccf800ULL,0xfec0c0f8c0c0fe00ULL,0xfec0c0f8c0c0c000ULL,0x7cc6c0c0cec67c00ULL,0xc6c6c6fec6c6c600ULL,0x7e18181818187e00ULL,0x606060606c67c00ULL,0xc6ccd8f0d8ccc600ULL,0xc0c0c0c0c0c0fe00ULL,0xc6eefefed6c6c600ULL,0xc6e6f6decec6c600ULL,0x7cc6c6c6c6c67c00ULL,0xfcc6c6fcc0c0c000ULL,0x7cc6c6c6d6de7c06ULL,0xfcc6c6fcd8ccc600ULL,0x7cc6c07c06c67c00ULL,0xff18181818181800ULL,0xc6c6c6c6c6c6fe00ULL,0xc6c6c6c6c67c3800ULL,0xc6c6c6c6d6fe6c00ULL,0xc6c66c386cc6c600ULL,0xc6c6c67c1830e000ULL,0xfe060c183060fe00ULL,0x3c30303030303c00ULL,0xc06030180c060200ULL,0x3c0c0c0c0c0c3c00ULL,0x10386cc600000000ULL,0xffULL,0x18180c0000000000ULL,0x7c067ec67e00ULL,0xc0c0c0fcc6c6fc00ULL,0x7cc6c0c67c00ULL,0x606067ec6c67e00ULL,0x7cc6fec07c00ULL,0x1c36307830307800ULL,0x7ec6c67e06fcULL,0xc0c0fcc6c6c6c600ULL,0x1800381818183c00ULL,0x60006060606c67cULL,0xc0c0ccd8f8ccc600ULL,0x3818181818183c00ULL,0xccfefed6d600ULL,0xfcc6c6c6c600ULL,0x7cc6c6c67c00ULL,0xfcc6c6fcc0c0ULL,0x7ec6c67e0606ULL,0xfcc6c0c0c000ULL,0x7ec07c06fc00ULL,0x18187e1818180e00ULL,0xc6c6c6c67e00ULL,0xc6c6c67c3800ULL,0xc6c6d6fe6c00ULL,0xc66c386cc600ULL,0xc6c6c67e06fcULL,0xfe0c3860fe00ULL,0xe18187018180e00ULL,0x1818180018181800ULL,0x7018180e18187000ULL,0x76dc000000000000ULL,0x10386cc6c6fe00ULL,0x7cc6c0c0c0d67c30ULL,0xc600c6c6c6c67e00ULL,0xe007cc6fec07c00ULL,0x7e813c067ec67e00ULL,0x66007c067ec67e00ULL,0xe0007c067ec67e00ULL,0x18187c067ec67e00ULL,0x7cc6c0d67c30ULL,0x7e817cc6fec07c00ULL,0x66007cc6fec07c00ULL,0xe0007cc6fec07c00ULL,0x6600381818183c00ULL,0x7c82381818183c00ULL,0x7000381818183c00ULL,0xc6107cc6fec6c600ULL,0x3838007cc6fec600ULL,0xe00fec0f8c0fe00ULL,0x7f0c7fcc7f00ULL,0x3f6cccffcccccf00ULL,0x7c827cc6c6c67c00ULL,0x66007cc6c6c67c00ULL,0xe0007cc6c6c67c00ULL,0x7c8200c6c6c67e00ULL,0xe000c6c6c6c67e00ULL,0x66006666663e067cULL,0xc67cc6c6c6c67c00ULL,0xc600c6c6c6c6fe00ULL,0x18187ed8d8d87e18ULL,0x386c60f06066fc00ULL,0x66663c187e187e18ULL,0xf8ccccfac6cfc6c3ULL,0xe1b183c1818d870ULL,0xe007c067ec67e00ULL,0x1c00381818183c00ULL,0xe007cc6c6c67c00ULL,0xe00c6c6c6c67e00ULL,0xfe00fcc6c6c600ULL,0xfe00c6e6f6dece00ULL,0x3c6c6c3e007e0000ULL,0x3c66663c007e0000ULL,0x1800181830663c00ULL,0xfcc0c00000ULL,0xfc0c0c0000ULL,0xc6ccd83f63cf8c0fULL,0xc3c6ccdb376dcf03ULL,0x1800181818181800ULL,0x3366cc66330000ULL,0xcc663366cc0000ULL,0x2288228822882288ULL,0x55aa55aa55aa55aaULL,0xdd77dd77dd77dd77ULL,0x1818181818181818ULL,0x18181818f8181818ULL,0x1818f818f8181818ULL,0x36363636f6363636ULL,0xfe363636ULL,0xf818f8181818ULL,0x3636f606f6363636ULL,0x3636363636363636ULL,0xfe06f6363636ULL,0x3636f606fe000000ULL,0x36363636fe000000ULL,0x1818f818f8000000ULL,0xf8181818ULL,0x181818181f000000ULL,0x18181818ff000000ULL,0xff181818ULL,0x181818181f181818ULL,0xff000000ULL,0x18181818ff181818ULL,0x18181f181f181818ULL,0x3636363637363636ULL,0x363637303f000000ULL,0x3f3037363636ULL,0x3636f700ff000000ULL,0xff00f7363636ULL,0x3636373037363636ULL,0xff00ff000000ULL,0x3636f700f7363636ULL,0x1818ff00ff000000ULL,0x36363636ff000000ULL,0xff00ff181818ULL,0xff363636ULL,0x363636363f000000ULL,0x18181f181f000000ULL,0x1f181f181818ULL,0x3f363636ULL,0x36363636ff363636ULL,0x1818ff18ff181818ULL,0x18181818f8000000ULL,0x1f181818ULL,0xffffffffffffffffULL,0xffffffffULL,0xf0f0f0f0f0f0f0f0ULL,0xf0f0f0f0f0f0f0fULL,0xffffffff00000000ULL,0x76dcc8dc7600ULL,0x386c6c786c666c60ULL,0xfec6c0c0c0c000ULL,0xfe6c6c6c6c00ULL,0xfe6030183060fe00ULL,0x7ed8d8d87000ULL,0x666666667c60c0ULL,0x76dc1818181800ULL,0x7e183c66663c187eULL,0x3c66c3ffc3663c00ULL,0x3c66c3c36666e700ULL,0xe180c7ec6c67c00ULL,0x7edbdb7e0000ULL,0x60c7edbdb7e60c0ULL,0x3860c0f8c0603800ULL,0x78cccccccccccc00ULL,0x7e007e007e0000ULL,0x18187e1818007e00ULL,0x603018306000fc00ULL,0x183060301800fc00ULL,0xe1b1b1818181818ULL,0x1818181818d8d870ULL,0x1818007e00181800ULL,0x76dc0076dc0000ULL,0x386c6c3800000000ULL,0x1818000000ULL,0x18000000ULL,0xf0c0c0cec6c3c1cULL,0x786c6c6c6c000000ULL,0x7c0c7c607c000000ULL,0x3c3c3c3c0000ULL,0x10000000000000ULL};


}}}
