local discordRPC = require "discordRPC"

local startTime = os.time()
local aircraft = "N/A"
local image = "na"

function refresh()
    dataref("acf", "sim/aircraft/view/acf_descrip", "readable")
    dataref("acfIcao", "sim/aircraft/view/acf_ICAO", "readable")
    dataref("knots", "sim/flightmodel/position/indicated_airspeed", "readable")
    dataref("altitude", "sim/flightmodel/position/elevation", "readable")
    altitude = altitude * 3.28084

    if acfIcao == "E170" then
        aircraft = "Embraer E170"
        image = "e-jets"
    elseif acfIcao == "E195" then
        aircraft = "Embrear E195"
        image = "e-jets"
    else
        aircraft = acf
    end

    discordRPC.updatePresence({
        ["state"] = math.floor(altitude) .. "ft, " .. math.floor(knots) .. "kts"
        ["details"] = aircraft
        ["startTimestamp"] = startTime
        ["largeImageKey"] = image
        ["largeImageText"] = acfIcao
        ["smallImageKey"] = "xp"
        ["smallImageText"] = "XP-RichPresence v0.1a"
    })
end

local function run()
    discordRPC.initialize("579668847846752266", false, "269950")
    do_on_exit("discordRPC.clearPresence()")
    do_often("refresh()")