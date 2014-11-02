#!/bin/bash -xe
python tools/run-style-tool.py cpplint &> style_errors.txt
cat style_errors.txt | grep -v Done
