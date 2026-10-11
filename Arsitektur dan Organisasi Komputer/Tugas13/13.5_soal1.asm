# =====================================================
# TUGAS 13.5 - SOAL 1
# hasil = a × b, dengan a = 12, b = 8
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanHasil : .asciiz "Hasil perkalian = "

.text
.globl main

main:
    li $t0, 12          # a = 12
    li $t1, 8           # b = 8

    # Perkalian: mult menghasilkan 64-bit di HI:LO
    mult $t0, $t1

    # Ambil hasil dari register LO
    mflo $s0            # $s0 = 12 * 8 = 96

    # Tampilkan
    li $v0, 4
    la $a0, pesanHasil
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall