<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Temperature extends Model
{
    use HasFactory;

    protected $table = 'temperatures'; // Nama tabel
    protected $fillable = ['temperature', 'humidity']; // Kolom yang bisa diisi
}

