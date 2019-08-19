#!/usr/bin/env python
# -*- coding: utf-8 -*-

import platform
from bincrafters import build_template_default


if __name__ == "__main__":
    builder = build_template_default.get_builder(pure_c=False)
    if platform.system() == "Windows":
        builder.remove_build_if(lambda build: "MT" in build.settings["compiler.runtime"])
    builder.run()

