import unittest
import os
import code as c

class TaxPayer:
    def __init__(self, username, password):
        self.username = username
        self.password = password
        self.prof_picture = None
        self.tax_form_attachment = None

    # Helper function to validate paths against an allow list
    def is_valid_path(self, base_dir, path):
        full_path = os.path.abspath(os.path.join(base_dir, path))
        # Ensure the path is within the base directory
        return full_path.startswith(base_dir)

    def get_prof_picture(self, path=None):
        if not path:
            return None  # Optional profile picture, no action needed

        base_dir = os.path.dirname(os.path.abspath(__file__))

        # Allow-list validation
        if not self.is_valid_path(base_dir, path):
            return None

        prof_picture_path = os.path.normpath(os.path.join(base_dir, path))
        try:
            with open(prof_picture_path, 'rb') as pic:
                picture = bytearray(pic.read())
        except (FileNotFoundError, IOError):
            return None

        return prof_picture_path

    def get_tax_form_attachment(self, path=None):
        if not path:
            raise Exception("Error: Tax form is required for all users")

        base_dir = os.path.dirname(os.path.abspath(__file__))

        # Allow-list validation
        if not self.is_valid_path(base_dir, path):
            raise Exception("Error: Invalid tax form path")

        try:
            with open(path, 'rb') as form:
                tax_data = bytearray(form.read())
        except (FileNotFoundError, IOError):
            raise Exception("Error: Tax form not found")

        return path
