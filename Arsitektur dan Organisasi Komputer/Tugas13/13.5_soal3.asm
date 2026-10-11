# =====================================================
# TUGAS 13.5 - SOAL 3
# luas = panjang × lebar, panjang=15, lebar=8
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanLuas : .asciiz "Luas persegi panjang = "

.text
.globl main

main:
    li $t0, 15          # panjang = 15
    li $t1, 8           # lebar = 8

    # Hitung luas = panjang * lebar
    mult $t0, $t1
    mflo $s0            # $s0 = 15 * 8 = 120

    # Tampilkan
    li $v0, 4
    la $a0, pesanLuas
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall