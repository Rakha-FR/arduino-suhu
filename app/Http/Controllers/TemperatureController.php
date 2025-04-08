<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Temperature;

class TemperatureController extends Controller
{
    public function store(Request $request)
    {
        // Validasi data
        $validatedData = $request->validate([
            'temperature' => 'required|numeric',
            'humidity' => 'required|numeric',
        ]);

        // Simpan ke database
        Temperature::create($validatedData);
        
        return response()->json(['message' => 'Data suhu berhasil disimpan'], 201);
    }

    public function index()
    {
        // Ambil data terakhir berdasarkan ID atau timestamp
        $latestTemperature = Temperature::latest()->first();

        // Jika tidak ada data, kembalikan pesan
        if (!$latestTemperature) {
            return response()->json(['message' => 'Belum ada data suhu'], 404);
        }

        return response()->json($latestTemperature);
    }
}
