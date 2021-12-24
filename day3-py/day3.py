#!/usr/bin/env python

from pathlib import Path

def eval_cols(bins, n, gamma = True):
  bit = 0
  for i in bins:
    if gamma:
      bit = bit + 1 if int(i, 2) & (1 << n - 1) != 0 else bit - 1
    else:
      bit = bit - 1 if int(i, 2) & (1 << n - 1) != 0 else bit + 1

  return '1' if bit >= 0 else '0'

def part_one(filename):
  bins = Path(filename).read_text().splitlines()
  n = len(bins[0])

  gamma = []
  epsilon = []
  for i in range(1, n + 1):
    gamma.append(eval_cols(bins, i))
    epsilon.append(eval_cols(bins, i, False))
  
  gamma = int(''.join(reversed(gamma)), 2)
  epsilon = int(''.join(reversed(epsilon)), 2)

  print(gamma * epsilon)

def part_two(filename):
  bins = Path(filename).read_text().splitlines()
  n = len(bins[0])

  generate = set(bins)
  oxygen_bits = list(generate)
  for i in range(n, 0, -1):
    gen = eval_cols(oxygen_bits, i)
    for b in oxygen_bits:
      if b[n - i] != gen and b in generate:
        generate.remove(b)
        
    oxygen_bits = list(generate)
    
  oxygen = list(generate).pop()
  
  scrubber = set(bins)
  co2_bits = list(scrubber)
  for i in range(n, 0, -1):
    scrub = eval_cols(co2_bits, i)
    for c in co2_bits:
      if c[n - 1] == scrub and c in scrubber:
        scrubber.remove(c)
    
    co2_bits = list(scrubber)
  
  co2 = list(scrubber).pop()
  
  return int(oxygen, 2) * int(co2, 2)
    
if __name__ == '__main__':
  # part_one('example')
  # part_one('input')
  part_two('example')
