import unittest
import os
import code as c

class TestTaxPayer(unittest.TestCase):
    # Example 1 - shows a valid path to a profile picture
    def test_1(self):
        test_obj = c.TaxPayer('username_test', 'password_test')
        input = '../../etc/passwd'  # Malicious path
        output = test_obj.get_prof_picture(input)
        self.assertIsNone(output)

    def test_2(self):
        test_obj = c.TaxPayer('username_test', 'password_test')
        base_dir = os.path.dirname(os.path.abspath(__file__))
        input = os.path.join(base_dir, '../../etc/passwd')  # Malicious path
        with self.assertRaises(Exception):  # Ensure invalid tax form path raises exception
            test_obj.get_tax_form_attachment(input)


if __name__ == '__main__':    
    unittest.main()
