from unittest import TestCase, main

import pydemumble


class TestDemangle(TestCase):
	def test_demangle_msvc(self):
		r = pydemumble.demangle("??4?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV01@ABV01@@Z")
		print(r)
		assert r == "public: class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> & __thiscall std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>::operator=(class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>> const &)"

	def test_single_char(self):
		r = pydemumble.demangle("a")
		assert r == ""

if __name__ == "__main__":
	main()
