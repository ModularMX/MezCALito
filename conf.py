# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information
import os
import sys
sys.path.insert(0, os.path.abspath("."))

project = 'mezcalito'
copyright = '2023, modular'
author = 'diego'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration
extensions = [
    'sphinx.ext.autodoc',
    'sphinx_needs',
    'sphinxcontrib.plantuml'
]

# The file extensions of source files. Sphinx considers the files with this suffix as sources. 
# The value can be a dictionary mapping file extensions to file types. For example:
source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown'
}

# The document name of the “root” document, that is, the document that contains the root toctree 
# directive. Default is 'index'.
root_doc = 'index'

# A list of paths that contain extra templates (or templates that overwrite builtin/theme-specific templates). 
# Relative paths are taken as relative to the configuration directory.
templates_path = ['Build/_templates']

# A list of glob-style patterns [1] that are used to find source files. They are matched against the 
# source file names relative to the source directory, using slashes as directory separators on all 
# platforms. The default is **, meaning that all files are recursively included from the source directory.
#include_patterns = ['./docs']

# A list of glob-style patterns [1] that should be excluded when looking for source files. They are 
# matched against the source file names relative to the source directory, using slashes as directory 
# separators on all platforms.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output
html_theme = 'alabaster'
html_static_path = []

# -- Sphinx needs HTML output -------------------------------------------------
# https://sphinx-needs.readthedocs.io/en/latest/

# Forces the user to set an ID for each need, which gets defined. So no ID is autogenerated any more, 
# if this option is set to True:
needs_id_required = True
# This option mostly affects the roles need_outgoing and need_incoming by showing the title beside the 
# ID of the linked need. Can be combined with needs_show_link_type. Activate it by setting it on True 
# in your conf.py:
needs_show_link_title = False

# Defines a set of valid statuses, which are allowed to be used inside documentation. If we detect a 
# status not defined, an error is thrown and the build stops. The checks are case sensitive.
needs_statuses = [
    dict(name="open", description="Nothing done yet"),
    dict(name="draft", description="it is not valid for development yet"),
    dict(name="in progress", description="Someone is working on it"),
    dict(name="implemented", description="Work is done and implemented")
]
# Defines a set of valid tags, which are allowed to be used inside documentation. If we detect a tag not 
# defined, an error is thrown and the build stops. The checks are case sensitive.
needs_tags = [
    dict(name="autosar", description="main autosar requirements"),
    dict(name="bsw", description="basic software modules (mcal layer)")
]
# Defines a regular expression used to validate all manually set IDs and to generate valid IDs for 
# needs without a given ID. Default value: ^[A-Z0-9_]{5,}
needs_id_regex = '^[a-zA-Z0-9_]{5,}'

# $ sphinx-build -b html docs Build/sphinx/_build -c ./ -W
# $ firefox build/sphinx/index.html
