#!/bin/bash
ip -V | awk -F '-ss' '{print "20" substr($2,1,2) "-" substr($2,3,2) "-" substr($2,5,2)}'