-- Configuration
spdDisagree = true -- Enables SPD DISAGREE warning.
altDisagree = true -- Enables ALT DISAGREE warning.
classicDetails = false -- Disables showing the Tail Number. More functionality soon.

-- Program, dont touch unless you know what you are doing!
discordRPC = require "discordRPC"
startTime = os.time()
aircraft = "N/A"
image = "na"

function refresh()
    dataref("acf", "sim/aircraft/view/acf_descrip", "readable")
    dataref("acfIcao", "sim/aircraft/view/acf_ICAO", "readable")
    dataref("tailNum", "sim/aircraft/view/acf_tailnum", "readable")
    dataref("kts", "sim/flightmodel/position/indicated_airspeed", "readable")
    dataref("kts2", "sim/flightmodel/position/indicated_airspeed2", "readable")
    dataref("alt", "sim/cockpit2/gauges/indicators/altitude_ft_pilot", "readable")
    dataref("alt2", "sim/cockpit2/gauges/indicators/altitude_ft_copilot", "readable")

    if (spdDisagree == true) then
        if (kts ~= kts2) then
            kts = "SPD DISAGREE"
        else
            kts = math.floor(kts) .. "kts"
        end
    else
        kts = math.floor(kts) .. "kts"
    end

    if (altDisagree == false) then
        if (alt ~= alt2) then
            altitude = "ALT DISAGREE"
        else
            altitude = math.floor(alt) .. "ft"
        end
    else
        altitude = math.floor(alt) .. "ft"
    end

    if (acfIcao == "E170") then
        aircraft = "Embraer E170"
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "E175") then
        aircraft = "Embrear E175"
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "E190") then
        aircraft = "Embrear E190"
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "E195") then
        aircraft = "Embrear E195"
        image = "e-jets"
        altDisagree = false
    elseif (acfIcao == "DR40") then
        aircraft = "Robin DR401"
        image = "dr40"
    elseif (acfIcao == "C172") then
        aircraft = "Cessna 172 Skyhawk"
        image = "c172"
    elseif (acfIcao == "B737") then
        aircraft = "Boeing 737-700"
        image = "737ng"
    elseif (acfIcao == "B738") then
        aircraft = "Boeing 737-800"
        image = "737ng"
    elseif (acfIcao == "B739") then
        aircraft = "Boeing 737-900ER"
        image = "737ng"
    elseif (acfIcao == "A318") then
        aircraft = "Airbus A318"
        image = "a320"
    elseif (acfIcao == "A319") then
        aircraft = "Airbus A319"
        image = "a320"
    elseif (acfIcao == "A320") then
        aircraft = "Airbus A320"
        image = "a320"
    elseif (acfIcao == "A321") then
        aircraft = "Airbus A321"
        image = "a320"
    elseif (acfIcao == "B752") then
        aircraft = "Boeing 757-200"
        image = "b757"
    elseif (acfIcao == "B753") then
        aircraft = "Boeing 757-300"
        image = "b757"
    elseif (acfIcao == "MD82") then
        aircraft = "McDonnell Douglass MD-82"
        image = "md88"
    elseif (acfIcao == "MD88") then
        aircraft = "McDonnell Douglass MD-88"
        image = "md88"
    elseif (acfIcao == "D328") then
        aircraft = "Dornier 328"
        image = "d328"
    else
        aircraft = acf
    end

    if (classicDetails == true) then
        discordRPC.updatePresence({
            ["state"] = altitude .. ", " .. kts,
            ["details"] = aircraft .. " (" .. string.sub(tailNum, 3, -1) .. ")",
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageKey"] = "xp",
            ["smallImageText"] = "v0.5a"
        })
    else
        discordRPC.updatePresence({
            ["state"] = altitude .. ", " .. kts,
            ["details"] = aircraft,
            ["startTimestamp"] = startTime,
            ["largeImageKey"] = image,
            ["largeImageText"] = acfIcao,
            ["smallImageKey"] = "xp",
            ["smallImageText"] = "v0.5a"
        })
    end
end

function run()
    discordRPC.initialize("579668847846752266", false, "269950")
    do_on_exit("discordRPC.clearPresence()")
    do_often("refresh()")
end

local ok = xpcall(run, function(err)
    logMsg(err)
end)