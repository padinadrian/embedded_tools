#! /usr/bin/env bash


pandoc\
    --from=gfm\
    --metadata title="PlayStation 2 Controller Interface"\
    --metadata author="Adrian Padin (padin.adrian@gmail.com)"\
    --metadata date="December 6, 2020"\
    -s\
    -o ps2.html\
    ps2.md
