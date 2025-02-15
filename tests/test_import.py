from unittest import TestCase, main


class TestImport(TestCase):
	def test_import(self):
		import pydemumble
		assert hasattr(pydemumble, "__version__")


if __name__ == "__main__":
	main()
