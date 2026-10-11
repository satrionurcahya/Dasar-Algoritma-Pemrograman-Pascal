# =====================================================
# TUGAS 13.3 - SOAL 1
# if (a > b) hasil = a; else hasil = b;
# a = 25, b = 18
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanHasil : .asciiz "Nilai terbesar = "

.text
.globl main

main:
    li $t0, 25          # a = 25
    li $t1, 18          # b = 18

    # Bandingkan a dan b
    # slt $t2, $t1, $t0 -> $t2 = 1 jika b < a (artinya a > b)
    slt $t2, $t1, $t0   # $t2 = 1 karena 18 < 25

    beq $t2, $zero, else_branch   # jika $t2 == 0, lompat ke else

    # Blok if: hasil = a
    move $s0, $t0
    j   selesai

else_branch:
    # Blok else: hasil = b
    move $s0, $t1

selesai:
    # Tampilkan hasil
    li $v0, 4
    la $a0, pesanHasil
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall